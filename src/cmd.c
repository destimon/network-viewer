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

}

void cmd_help(t_input *inp)
{
	printf("Network Viewer\n\nstart - start daemon\nstop - stop daemon\nhelp\n\nauthor: github.com/destimon\n");
}