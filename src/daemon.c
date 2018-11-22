#include "../inc/nviewer.h"

static void create_pidfile(pid_t pid)
{
	FILE *fp = NULL;

	/* Should protect case where path doesn't exist */
	fp = fopen(PIDFILE, "w+");
	if (fp)
	{
		fprintf(fp, "%d\n", pid);
		fclose(fp);
	}
	else
	{
		throw_error(strerror(errno));
	}
}

void start_daemon(t_config *cfg)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		throw_error(ERR_FORK_FAIL);
	else if (pid == 0)
	{
		daemon_prefsetup();
		start_sniff(cfg);
	}
	else
	{
		printf("pid of child: %d\n", pid);
		create_pidfile(pid);
		exit(0);
	}
}

void stop_daemon()
{
	pid_t pid;

	pid = check_pidfile();
	if (pid < 0)
		throw_error(ERR_DAEMON_NOTRUNNING);
	else
	{
		if (kill(pid, SIGTERM) < 0)
		{
			throw_error(strerror(errno));
		}
		else
		{
			remove(PIDFILE);
			printf("daemon successfuly terminated.\n");
		}
	}
}