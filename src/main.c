#include "../inc/nviewer.h"

/* Array of function's pointers initialization */
t_command g_cmds[] = {
	{"start", "Start Daemon process", &cmd_start},
	{"stop", "Stop Daemon process", &cmd_stop},
	{"show", "Stop Daemon process", &cmd_stop},
	{"select", "Stop Daemon process", &cmd_select},
	{"stat", "Stop Daemon process", &cmd_stop},
	{"exit", "Stop Daemon process", &cmd_stop},
	{"--help", "Yes, it is.", &cmd_help}
};

/* Just because while(1) causes endless loop warning */
static int is_user_a_goat(void)
{
	return (1);
}

/*
** Dunno what was required in task, shell or just arg parse 
** so i decided to implement they both
*/

int main(int argc, char **argv)
{
	t_input *inp;
	char *buf;
	size_t size = 1024 + 1;

	if (ft_elems(argv) == 1)
	{
		/* Shell */
		while (is_user_a_goat())
		{
			buf = (char*)malloc(sizeof(char) * size);
			printf(PROMPT);
			if (getline(&buf, &size, stdin) > 0)
			{
				inp = alloc_input(ft_strsplit(buf, ' '));
				if (inp)
					entry_switcher(inp);
			}
			free(buf);
		}
	}
	else
	{
		/* Args handle */
		inp = alloc_input(&argv[1]);
		if (inp)
			entry_switcher(inp);
	}
	return (0);
}