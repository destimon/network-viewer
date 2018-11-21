#ifndef STRUCTS_H
# define STRUCTS_H

#include "nviewer.h"

typedef struct	s_input
{
	char		**query;
	int			cmd;
	int			flags; /* TODO: implement storage for
					      flags in binary format */
}				t_input;

/*
** Interface -> Senders List(list of ip in
** txt formate) 
*/

typedef struct s_sender
{
	char *ip;
	size_t recieved_count;
	struct s_sender *next;
}				t_sender;

typedef struct s_iface
{
	char *dev;
	struct s_sender *begin_sender;
}				t_iface;

typedef struct s_config
{
	char *dev;
}				t_config;

struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* dont fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};


#endif