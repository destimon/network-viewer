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

void print_padding(int size)
{
	int i = 0;

	while (i < size)
	{
		printf(" ");
		i++;
	}
}

int get_longest_value()
{
	char **line = NULL;
	char buf[1024 + 1];
	int longest = 0;
	FILE *fp;

	fp = fopen(LOGFILE, "r");
	if (fp)
	{
		while (fgets(buf, 1024, fp) != NULL)
		{
			line = ft_strsplit(buf, ' ');
			if (!line)
				return (0);
			if (line[1])
			{
				if (longest < (int)strlen(line[1]))
					longest = strlen(line[1]);
			}
			ft_two_del(line);
		}
		return (longest);
	}
	return (0);
}

int ip_comparsion(const void * a, const void * b)
{
	t_ip *ip1 = (t_ip*)a;
	t_ip *ip2 = (t_ip*)b;

	uint64_t va = ip1->address;
	uint64_t vb = ip2->address;

   return 
        va < vb
        ? 1                 
        : va == vb
        ? 0                 
        : -1              
        ;                   
}



void daemon_prefsetup()
{
	pid_t sid;

	/* Change mask, dir. Close descs, set sid. */
	umask(0);
	sid = setsid();
	if (sid < 0)
		exit (1);
	// chdir("/tmp");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}