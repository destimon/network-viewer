#include "../inc/nviewer.h"

void cmd_start(t_input *inp)
{
	FILE *fd = NULL;
	printf("START");
	
	// fork

	// if parent
	// 	exit
	// elif child
	// 	Do daemon stuff

	pid_t pid;
	pid_t sid;

	pid = fork();
	if (pid < 0)
		throw_error(ERR_FORK_FAIL);
	else if (pid == 0)
	{
		umask(0);
		sid = setsid();
		if (sid < 0)
			exit (1);
		chdir("/tmp");
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		fd = fopen("log.txt", "w+");
		while (1)
		{
			sleep(2);
			fprintf(fd, "Logging info ...\n");
			fflush(fd);
		} 
		fclose(fd);
	}
	else
	{
		printf("pid of child: %d\n", pid);
		exit(0);
	}
}

void cmd_stop(t_input *inp)
{
	printf("STOP");	
}