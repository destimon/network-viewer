#include "../inc/nviewer.h"

FILE *fp = NULL;

static void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet
)
{
	static int i = 0;

	/* First, lets make sure we have an IP packet */
    struct ether_header *eth_header;

    eth_header = (struct ether_header *) packet;
    fp = fopen(LOGFILE, "w+");
    // if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
    //     fprintf(fp, "Not an IP packet. Skipping...\n\n");
    //     return;
    // }
    fprintf(fp, "Packets: %d\n", i);
    fclose(fp);
    i++;
}


int start_sniff(t_config *cfg)
{
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10000; /* In milliseconds */

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
    pcap_loop(handle, 0, my_packet_handler, NULL);
    return (0);
}