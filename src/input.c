#include "../inc/nviewer.h"

t_input *alloc_input(char *buf)
{
	t_input *inp;

	if (!buf)
		return (NULL);
	inp = (t_input*)malloc(sizeof(t_input));
	if (inp)
	{
		inp->buf = strtok(buf, "\n");
		inp->cmd = 0;
		inp->flags = 0;
		return (inp);
	}
	return (NULL);
}

void entry_switcher(t_input *inp)
{
	if (!inp->buf)
		return;
	while (inp->cmd < MAX_CMD)
	{
		// Travel trough function pointer array
		// to find the command we need
		if (strcmp(inp->buf, g_cmds[inp->cmd].name) == 0)
		{
			g_cmds[inp->cmd].func_ptr(inp);
			exit(0) ; // Exit after succesful operation
		}
		inp->cmd++;
	}
	// And if we didn't find, simply - show error
	throw_error(ERR_CMD_NOTFOUND);
}