#ifndef NVIEWER_H
# define NVIEWER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>


#define PROMPT "nviewer> "
#define MAX_CMD 2

/*
** ERRORS
*/

#define ERR_CMD_NOTFOUND "command not found."
#define ERR_FORK_FAIL "fork failed."

typedef struct	s_input
{
	char		*buf;
	int			cmd;
	int			flags; // TODO: implement storage for
					   // flags in binary format
}				t_input;

typedef struct s_command
{
	char *name;
	char *desc;
	void (*func_ptr)(t_input *);
}				t_command;

extern t_command g_cmds[];

/*
** INPUT.C
*/

t_input *alloc_input(char *buf);
void entry_switcher(t_input *inp);

/*
** CMD.C
*/

void cmd_start(t_input *inp);
void cmd_stop(t_input *inp);

/*
** ERRORS.C
*/

void throw_error(char *msg);

#endif