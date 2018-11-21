#include "../inc/nviewer.h"

t_input *alloc_input(char **arg)
{
	t_input *inp;

	if (!arg)
		return (NULL);
	inp = (t_input*)malloc(sizeof(t_input));
	if (inp)
	{
		inp->query = arg;
		inp->cmd = 0;
		inp->flags = 0;
		return (inp);
	}
	return (NULL);
}

void entry_switcher(t_input *inp)
{
	register int i = inp->cmd; /* register may be useless, but
								*  dude, it's C programming, GOTTA GO FAST */
	char *cmd;

	if (!inp->query || !inp->query[0])
		return;
	cmd = strtok(inp->query[0], "\n"); /* Delete linebreak from end */
	while (i < MAX_CMD)
	{
		// Travel trough function pointer array
		// to find the command we need
		if (ft_strequ(cmd, g_cmds[i].name))
		{
			g_cmds[i].func_ptr(inp);
			return ;
		}
		i++;
	}
	// And if we didn't find, simply - show error
	throw_error(ERR_CMD_NOTFOUND);
}