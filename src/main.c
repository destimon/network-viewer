#include "../inc/nviewer.h"

t_command g_cmds[] = {
	{"start", "Start Daemon process", &cmd_start},
	{"stop", "Stop Daemon process", &cmd_stop}
};


int main(int argc, char **argv)
{
	t_input *inp;
	char *buf;
	size_t size = 1024;

	while (1)
	{
		buf = (char*)malloc(sizeof(char) * size);
		printf(PROMPT);
		if (getline(&buf, &size, stdin) > 0)
		{
			inp = alloc_input(buf);
			if (inp)
				entry_switcher(inp);
		}
		free(buf);
	}
	return (0);
}