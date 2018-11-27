#include "../inc/nviewer.h"

FILE *fp = NULL;
struct s_ip_array g_sarr;

static void *listen_and_reply_cli() /* Я рэпер, йоу */
{
	while (1)
	{
		sleep(1); /* Delay for thread 1 sec */
		handle_listening(g_sarr);
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

	while (i < g_sarr.array_size)
	{
		if (g_sarr.ip_array[i].address == ip_decimal)
		{
			g_sarr.ip_array[i].packets += 1;
			return ;
		}
		i++;
	}
	/* The new IP passed, so we expand array if capacity is low */
	if (g_sarr.array_capacity <= g_sarr.array_size)
	{
		g_sarr.array_capacity *= 2;
		g_sarr.ip_array = realloc(g_sarr.ip_array, sizeof(t_ip) * g_sarr.array_capacity);
	}
	/* Insert top */
	if (ip_decimal > g_sarr.ip_array[0].address)
	{
		memmove(&g_sarr.ip_array[1], &g_sarr.ip_array[0], (g_sarr.array_size) * sizeof(t_ip));
		g_sarr.ip_array[0] = array_ip_element(ip, "1");
	}
	/* Insert Bottom (not bikini) */
	else if (ip_decimal < g_sarr.ip_array[g_sarr.array_size - 1].address)
	{
		g_sarr.ip_array[g_sarr.array_size] = array_ip_element(ip, "1");
	}
	/* Insert Middle */
	else
	{
		i = 0;
		while (i < g_sarr.array_size)
		{
			/* Find place between */
			if ((g_sarr.ip_array[i].address > ip_decimal) && (g_sarr.ip_array[i + 1].address < ip_decimal))
			{
				/* Array shift */
				memmove(&g_sarr.ip_array[i + 2], &g_sarr.ip_array[i + 1], (g_sarr.array_size - (i + 1)) * sizeof(t_ip));
				/* Insert between */
				g_sarr.ip_array[i + 1] = array_ip_element(ip, "1");
				break;
			}
			i++;
		}
	}
	g_sarr.array_size += 1;	
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
			g_sarr.ip_array = (t_ip*)malloc(sizeof(t_ip));
			g_sarr.array_capacity += 1;
			g_sarr.ip_array[g_sarr.array_size] = array_ip_element(line[1], line[2]);
			g_sarr.array_size += 1;
			ft_two_del(line);
		}
		/* Read the rest of file and push into array */
		while (fgets(buf, 1024, fp) != NULL)
		{
			line = ft_strsplit(buf, ' ');
			if (!line)
				return (NULL);
			if (g_sarr.array_capacity > g_sarr.array_size)
			{
				g_sarr.ip_array[g_sarr.array_size] = array_ip_element(line[1], line[2]);
				g_sarr.array_size += 1;
			}
			else
			{
				g_sarr.array_capacity *= 2;
				g_sarr.ip_array = realloc(g_sarr.ip_array, sizeof(t_ip) * g_sarr.array_capacity);
				g_sarr.ip_array[g_sarr.array_size] = array_ip_element(line[1], line[2]);
				g_sarr.array_size += 1;
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
	if (g_sarr.ip_array)
		insert_ip_element(ip);
	else
	{
		/* If array drain nothing - allocate first sniff element */
		g_sarr.ip_array = (t_ip*)malloc(sizeof(t_ip));
		g_sarr.array_capacity += 1;
		g_sarr.ip_array[g_sarr.array_size] = array_ip_element(ip, "1");
		g_sarr.array_size += 1;
	}
	/* Output to logfile */
	fp = fopen(LOGFILE, "w+");
	if (fp)
	{
		i = 0;
		while (i < g_sarr.array_size)
		{
			fprintf(fp, "%s %s %zd\n", g_sarr.devname, inet_ntoa(
				*(struct in_addr *)&g_sarr.ip_array[i].address), g_sarr.ip_array[i].packets);
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
	for (int i = 0; i < g_sarr.array_size; i++)
		fprintf(fp, "s: %zd\n", g_sarr.ip_array[i].address);
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

    g_sarr.devname = strdup(cfg->dev);
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