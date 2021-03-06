#ifndef NVIEWER_H
# define NVIEWER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <search.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#include <errno.h>

#include <signal.h>

#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/ethernet.h>

#include "structs.h"
#include "../lib/libft/libft.h"
#include "../lib/libft/get_next_line.h"

#define LISTEN_DELAY 2

#define PROMPT "nviewer> "
#define MAX_CMD 7

/*
** SNIFF
*/

#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define SIZE_ETHERNET 14

/*
** FILES
*/

#define PIDFILE "nviewer.pid"
#define LOGFILE "nviewer.log"
#define LOGFILE2 "nviewer.log.2"
#define ERRFILE "nviewer.errors"
#define CONFILE "nviewer.conf"
#define DEBFILE "nviewer.debug"

/*
** VARS
*/

enum conf_variables {
	VAR_IFACE,
	VAR_SUP /* 2ch */
} conf_vars;

/*
** ERRORS
*/

#define ERR_CMD_NOTFOUND "command not found."
#define ERR_FORK_FAIL "fork failed."
#define ERR_DAEMON_RUNNING "daemon already running."
#define ERR_DAEMON_NOTRUNNING "daemon is not running."

typedef struct s_command
{
	char *name;
	char *desc;
	char *opts;
	void (*func_ptr)(t_input *);
}				t_command;

extern t_command g_cmds[];

/*
** INPUT.C
*/

t_input *alloc_input(char **arg);
void entry_switcher(t_input *inp);

/*
** CMD.C
*/

void cmd_start(t_input *inp);
void cmd_stop(t_input *inp);
void cmd_select(t_input *inp);
void cmd_show(t_input *inp);
void cmd_stat(t_input *inp);
void cmd_help(t_input *inp);
void cmd_exit(t_input *inp);

/*
** DAEMON.C
*/

void start_daemon(t_config *cfg);
void stop_daemon(void);

/*
** SNIFFER.C
*/

int start_sniff(t_config *cfg);

/*
** CONFIGURE.C
*/

char *getconf_var(char *varname);
void setconf_var(char *var, char *value);
t_config get_configure(void);

/*
** SEARCH.C
*/

void search_ip(t_input *inp);

/*
** PCI.C
*/

void handle_listening(struct s_ip_array sarr);

/*
** UTILS.C
*/

pid_t check_pidfile(void);
void daemon_prefsetup(void);
int get_longest_value(void);
void print_padding(int size);
int ip_comparsion(const void * a, const void * b);

/*
** ERRORS.C
*/

void throw_error(char *msg);

#endif