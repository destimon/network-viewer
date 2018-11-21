#include "../inc/nviewer.h"

/*
** @return If daemon already running - positive number.
*/

pid_t check_pidfile()
{
	FILE *fp = NULL;
	char a_pid[512 + 1];
	pid_t pid = -1;
	fp = fopen("nviewer.pid", "r");
	if (fp)
	{
		if (fgets(a_pid, 512, fp))
		{
			pid = atoi(a_pid);
			fclose(fp);
			return (getpgid(pid));
		}
		fclose(fp);
	}
	return (-1);
}

void daemon_prefsetup()
{
	pid_t sid;

	/* Change mask, dir. Close descs, set sid. */
	umask(0);
	sid = setsid();
	if (sid < 0)
		exit (1);
	chdir("/tmp");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}