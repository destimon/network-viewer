#include "../inc/nviewer.h"

FILE *fp = NULL;
char *devname;

static void packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet
)
{
	int size_ip;
	static int i = 0;
	const struct sniff_ip *ip;
	
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
    fp = fopen(LOGFILE, "a+");
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		fprintf(fp, "   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}
    fprintf(fp, "%s %s\n", devname, inet_ntoa(ip->ip_src));
    fclose(fp);
    i++;
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
        return 2;
     }     
    pcap_loop(handle, 0, packet_handler, NULL);
    return (0);
}