#ifndef STRUCTS_H
# define STRUCTS_H

#include "nviewer.h"

typedef struct	s_input
{
	char		*buf;
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

#endif