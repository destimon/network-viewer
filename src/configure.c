#include "../inc/nviewer.h"

char *getconf_var(char *varname)
{
	int fd;
	FILE *fp;
	char **var;
	char *line;

	if (!varname)
		return (NULL);
	fp = fopen(CONFILE, "r");
	if (fp)
	{
		fd = fileno(fp);
		/* Get each line with var until end */
		while (get_next_line(fd, &line) > 0)
		{
			/* Split line in 2d array */
			var = ft_strsplit(line, '=');
			free(line);
			if (var)
			{
				/* if desired var equal to current var */
				if (ft_strequ(var[0], varname))
				{
					if (var[1])
					{
						/* then we free 2d array and turn value of var */
						/* ft_two_del(var); <- Leaks with last iteration. */
						close(fd);
						return (var[1]);
					}
				}
				/* also each step free 2d array */
				ft_two_del(var);
			}
		}
		fclose(fp);
	}
	/* When we didn't find desired var or var is empty 
	we just turn NULL*/
	return (NULL);
}

void setconf_var(char *var, char *value)
{
	FILE *fp;
	int fd;
	char *tmp;
	char *fullvar;

	if (!var || !value)
		return ;
	fp = fopen(CONFILE, "w+");
	if (fp)
	{
		fd = fileno(fp);
		tmp = strdup("="); /* to avade leaks */
		fullvar = ft_strsjoin(3, var, tmp, value); /* [var] [=] [value] */
		free(tmp);
		ft_putstr_fd(fullvar, fd); /* print str in file desc */
		ft_putstr_fd("\n", fd);
		free(fullvar);
		fclose(fp);
	}
}

t_config get_configure()
{
	const char* const cvars[VAR_SUP] = {"iface", "sup"};
	t_config cfg;
	char *var_value;

	/* Setup for future stack of additional confs 
	don't wonder about cycle with 1 iteration.
	Hope i will have time. */
	for (int i = 0; i < VAR_SUP; i++)
	{
		if (var_value = getconf_var((char*)cvars[i]))
		{
			cfg.dev = var_value;
		}
		else
		{
			/* In case if conf file doesn't exist */
			setconf_var((char*)cvars[i], "wlp2s0");
			cfg.dev = "wlp2s0";
		}
	}
	return (cfg);
}