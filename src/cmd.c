#include "../inc/nviewer.h"

void cmd_start(t_input *inp)
{
	t_config cfg;

	(void)inp;
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
	(void)inp;
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
		|| !inp->query[2] || !ft_strequ(strtok(inp->query[2], "\n"), "count")
		|| !inp->query[1])
			throw_error("invalid syntax.");
	else
	{
		search_ip(inp);	
	}
}

void cmd_stat(t_input *inp)
{
	char buf[1024];
	char *line = NULL;
	int fd;
	
	bzero(buf, 1024);
	mkfifo("fifo", 0666);
	fd = open("fifo", O_WRONLY);
	dprintf(fd, "%s\n", inp->query[0]);
	if (inp->query[1])
		dprintf(fd, "%s\n", inp->query[1]);
	close(fd);
	fd = open("fifo", O_RDONLY);
	// read(fd, buf, sizeof(buf) + 1);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	close(fd);
}

void cmd_help(t_input *inp)
{
	int i = -1;

	(void)inp;
	printf("\033[1m\033[31mNetwork Viewer\033[0m\n\n");
	while (++i < MAX_CMD)
	{
		printf("\033[1m%s", g_cmds[i].name);
		if (g_cmds[i].opts)
			printf(" %s\n", g_cmds[i].opts);
		else
			printf("\n");
		printf("\033[0m%s\n\n", g_cmds[i].desc);
	}
}

void cmd_exit(t_input *inp)
{
	(void)inp;
	exit (0);
}