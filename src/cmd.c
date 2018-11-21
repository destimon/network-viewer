#include "../inc/nviewer.h"

void cmd_start(t_input *inp)
{
	t_config cfg;

	if (check_pidfile() < 0)
	{
		cfg = get_configure();
		start_daemon(&cfg);
	}
	else
		throw_error(ERR_DAEMON_RUNNING);
}

void cmd_stop(t_input *inp)
{
	stop_daemon();
}

void cmd_select(t_input *inp)
{
	if (!inp->query || ft_elems(inp->query) != 3
		|| !inp->query[1] || !ft_strequ(inp->query[1], "iface")
		|| !inp->query[2])
			throw_error("invalid syntax.");
	else
	{
		setconf_var("iface", inp->query[2]);
		printf("interface successfuly changed.\n");
	}
}

void cmd_show(t_input *inp)
{
	if (!inp->query || ft_elems(inp->query) != 3
		|| !inp->query[2] || !ft_strequ(inp->query[2], "count")
		|| !inp->query[1])
			throw_error("invalid syntax.");
	// else
	// {
	// 	setconf_var("iface", inp->query[2]);
	// 	printf("daemon successfuly terminated.\n");
	// }
}

void cmd_help(t_input *inp)
{
	printf("Network Viewer\n\nstart - start daemon\nstop - stop daemon\nhelp\n\nauthor: github.com/destimon\n");
}