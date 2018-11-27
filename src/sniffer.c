#include "../inc/nviewer.h"

FILE *fp = NULL;
t_ip *ip_array = NULL;
int array_size = 0;
int array_capacity = 0;
char *devname;

static void *listen_and_reply_cli() /* Я рэпер, йоу */
{
	char msg[1024 + 1];
	char *tmp;
	char **line = NULL;
	t_ip *tofind;
	t_ip key;
	int fd;

	while (1)
	{
		sleep(1);
		ft_bzero(msg, 1024 + 1);
		/* Read from fifo ip */
		mkfifo("fifo", 0666);
		fd = open("fifo", O_RDONLY);
		read(fd, msg, sizeof(msg));
		close(fd);
		/* Handle operation */
		line = ft_strsplit(msg, ' ');
		if (line)
		{
			/* Then write request */
			fd = open("fifo", O_WRONLY);
			if (ft_elems(line) == 2)
			{
				/* Response to show ip count */
				if (ft_strequ(line[0], "show"))
				{
					key.address = inet_addr(msg);
					tofind = bsearch(&key, ip_array, array_size, sizeof(t_ip), ip_comparsion);
					if (tofind)
						dprintf(fd, "%zd", tofind->packets);
					else
						dprintf(fd, "Not found.");	
				}
				/* Response to show stat of iface */
				else if (ft_strequ(line[0], "stat"))
				{
					
				}
			}
			else if (ft_elems(line) == 1)
			{
				/* Response to show all stat */
				if (ft_strequ(line[0], "stat"))
				{

				}
			}
			ft_two_del(line);
			close(fd);
		}
	}
}

static t_ip array_ip_element(char *ip, char *packets)
{
	t_ip ip_elem;

	ip_elem.address = inet_addr(ip);
	ip_elem.packets = (size_t)atoi(packets);
	return (ip_elem);
}

static void insert_ip_element(char *ip)
{
	uint64_t ip_decimal = inet_addr(ip);
	t_ip *tofind = NULL;
	t_ip key;
	int i = 0;

	while (i < array_size)
	{
		if (ip_array[i].address == ip_decimal)
		{
			ip_array[i].packets += 1;
			return ;
		}
		i++;
	}
	/* The new IP passed, so we expand array if capacity is low */
	if (array_capacity <= array_size)
	{
		array_capacity *= 2;
		ip_array = realloc(ip_array, sizeof(t_ip) * array_capacity);
	}
	/* Insert top */
	if (ip_decimal > ip_array[0].address)
	{
		memmove(&ip_array[1], &ip_array[0], (array_size) * sizeof(t_ip));
		ip_array[0] = array_ip_element(ip, "1");
	}
	/* Insert Bottom (not bikini) */
	else if (ip_decimal < ip_array[array_size - 1].address)
	{
		ip_array[array_size] = array_ip_element(ip, "1");
	}
	/* Insert Middle */
	else
	{
		i = 0;
		while (i < array_size)
		{
			/* Find place between */
			if ((ip_array[i].address > ip_decimal) && (ip_array[i + 1].address < ip_decimal))
			{
				/* Array shift */
				memmove(&ip_array[i + 2], &ip_array[i + 1], (array_size - (i + 1)) * sizeof(t_ip));
				/* Insert between */
				ip_array[i + 1] = array_ip_element(ip, "1");
				break;
			}
			i++;
		}
	}
	array_size += 1;	
}


static t_ip *init_ip_array()
{
	t_ip *tmp2 = NULL;
	char buf[1024 + 1];
	char **line = NULL;
	FILE *fp = NULL;


	fp = fopen(LOGFILE, "r+");
	if (fp)
	{
		/* One line to init array entry */
		if (fgets(buf, 1024, fp) != NULL)
		{
			line = ft_strsplit(buf, ' ');
			if (!line)
				return (NULL);
			ip_array = (t_ip*)malloc(sizeof(t_ip));
			array_capacity += 1;
			ip_array[array_size] = array_ip_element(line[1], line[2]);
			array_size += 1;
			ft_two_del(line);
		}
		/* Read the rest of file and push into array */
		while (fgets(buf, 1024, fp) != NULL)
		{
			line = ft_strsplit(buf, ' ');
			if (!line)
				return (NULL);
			if (array_capacity > array_size)
			{
				ip_array[array_size] = array_ip_element(line[1], line[2]);
				array_size += 1;
			}
			else
			{
				array_capacity *= 2;
				ip_array = realloc(ip_array, sizeof(t_ip) * array_capacity);
				ip_array[array_size] = array_ip_element(line[1], line[2]);
				array_size += 1;
			}
			ft_two_del(line);
		}
		fclose(fp);
	}
	return (NULL);
}

static void record_recieve(char *ip)
{ 
	FILE *fp = NULL;
	t_ip *tmp = NULL;
	int i;

	/* Check if array filled by logfile */
	if (ip_array)
		insert_ip_element(ip);
	else
	{
		/* If array drain nothing - allocate first sniff element */
		ip_array = (t_ip*)malloc(sizeof(t_ip));
		array_capacity += 1;
		ip_array[array_size] = array_ip_element(ip, "1");
		array_size += 1;
	}
	/* Output to logfile */
	fp = fopen(LOGFILE, "w+");
	if (fp)
	{
		i = 0;
		while (i < array_size)
		{
			fprintf(fp, "%s %s %zd\n", devname, inet_ntoa(*(struct in_addr *)&ip_array[i].address), ip_array[i].packets);
			i++;
		}
		fclose(fp);
	}
}

static void packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet)
{
	const struct sniff_ip *ip;
	int size_ip;
	
	(void)args; /* Sorry for shitcode to avade -Wall */
	(void)packet_header; /* But it would be useful in case if i modify this task */
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		/* fprintf(fp, "   * Invalid IP header length: %u bytes\n", size_ip); */
		return;
	}
	record_recieve(inet_ntoa(ip->ip_src));
	FILE *fp = fopen(DEBFILE, "w+");
	fprintf(fp, "------------------\n");
	for (int i = 0; i < array_size; i++)
		fprintf(fp, "s: %zd\n", ip_array[i].address);
	fclose(fp);
}


void *pcap_loop_thread(void *arg)
{
	pcap_t *handle = (pcap_t*)arg;

	pcap_loop(handle, 0, packet_handler, NULL);
}

int start_sniff(t_config *cfg)
{
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10000; /* In milliseconds */
    pthread_t thread[2];

    devname = strdup(cfg->dev);
    /* Open device for live capture */
    handle = pcap_open_live(
            cfg->dev,
            BUFSIZ,
            0,
            timeout_limit,
            error_buffer
        );
    if (handle == NULL) {
    	fp = fopen(ERRFILE, "a+");
        fprintf(fp, "Could not open device %s: %s\n", cfg->dev, error_buffer);
        fclose(fp);
        exit (0);
    }
    /* Allocate from logfile if possible */
    init_ip_array(); 

	/* Divide thread between listening packets and requests from cli */
	pthread_create( &thread[0], NULL, listen_and_reply_cli, NULL);
	pthread_create( &thread[1], NULL, pcap_loop_thread, (void*) handle);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
    return (0);
}