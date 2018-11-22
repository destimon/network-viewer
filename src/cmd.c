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
		|| !inp->query[2] || !ft_strequ(inp->query[2], "count\n")
		|| !inp->query[1])
			throw_error("invalid syntax.");
	else
	{
		search_ip(inp);	
	}
}

void cmd_stat(t_input *inp)
{
	char **line = NULL;
	char buf[1024 + 1];
	int longest_len = 0;
	FILE *fp = NULL;

	fp = fopen(LOGFILE, "r");
	longest_len = get_longest_value();	
	printf("INTERFACE");
	print_padding(longest_len - 3);
	printf("IP   ");
	printf("PACKETS    \n");
	printf("---------------------------------\n");
	if (inp->query && fp)
	{
		while (fgets(buf, 1024, fp) != NULL)
		{
			line = ft_strsplit(buf, ' ');
			if (!line)
				return ;
			if (ft_elems(inp->query) > 1)
			{
				
			}
			else
			{
				printf("%s", line[0]);
				print_padding(longest_len - strlen(line[1]) + 2);
				printf("%s", line[1]);
				printf("   ");
				printf("%s", line[2]);
			}
		}
		fclose(fp);
	}
}

void cmd_help(t_input *inp)
{
	printf("Network Viewer\n\nstart - start daemon\nstop - stop daemon\nhelp\n\nauthor: github.com/destimon\n");
}