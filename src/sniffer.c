#include "../inc/nviewer.h"

FILE *fp = NULL;
char *devname;

static void record_recieve(char *ip)
{ 
	FILE *tmpfile = NULL;
	char buf[1024 + 1];																																																																																																																																																																																																																						
	char **lines = NULL;
	char **tmp = NULL;
	int num = 0;
	bool is_recorded = false;

	fp = fopen(LOGFILE, "a+");
	tmpfile = fopen(LOGFILE2, "a+");
	if (fp && tmpfile)
	{
		while (fgets(buf, 1024, fp) != NULL)
		{
			tmp = ft_strsplit(buf, ' ');
			if (tmp)
			{
				/* if ip already recorded */
				if (ft_strequ(tmp[1], ip))
				{
					/* increment number of packets */
					lines = ft_strsplit(buf, ' ');
					num = atoi(lines[2]) + 1;
					fprintf(tmpfile, "%s %s %d\n", devname, ip, num);
					/* Tell program to add new ip */
					is_recorded = true;
				}
				else /* other lines re-record */
				{
					fprintf(tmpfile, "%s", buf);
				}
				ft_two_del(tmp);
			}
		}
		/* Add new ip */
		if (is_recorded == false)
			fprintf(tmpfile, "%s %s %d\n", devname, ip, 1);
		fclose(fp);
		fclose(tmpfile);
		remove(LOGFILE);
		rename(LOGFILE2, LOGFILE);
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
}


int start_sniff(t_config *cfg)
{
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10000; /* In milliseconds */

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
    pcap_loop(handle, 0, packet_handler, NULL);
    return (0);
}