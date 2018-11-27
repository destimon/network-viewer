#include "../inc/nviewer.h"

/*
** Notice:
** 
** Среди IPС выбрал FIFO. Возможно здесь shared memory
** Поэффективнее была бы, но мне FIFO привычнее.
**
** На счет logN скорости - я решил убрать квиксорт и
** просто заполнять массив в демоне сразу отсортированным
** ,а при запросе от CLI - через bsearch
** отправлять на FIFO уже сразу нужные данные.
**
** Запустил два треда через pthreads, в одном прослушивание CLI
** а в другом прослушивание пакетов, не уверен насколько это верно,
** но работает.
**
** Мем лики возможно не все успел все почистить, в виду того, что
** времени не оставалось, но через валграйнд почистил что мог.
** 
*/

void handle_listening(struct s_ip_array sarr)
{
	char msg[1024 + 1];
	char *tmp;
	char **line = NULL;
	t_ip *tofind;
	t_ip key;
	int fd;
	int i;

	ft_bzero(msg, 1024 + 1);
	/* Read from fifo ip */
	mkfifo("fifo", 0666);
	fd = open("fifo", O_RDONLY);
	read(fd, msg, sizeof(msg));
	close(fd);
	/* Handle operation */
	line = ft_strsplit(msg, ' ');
	if (line)
	{
		/* Then write request */
		fd = open("fifo", O_WRONLY);
		if (fd < 0)
			return ;
		if (ft_elems(line) == 2)
		{
			/* Response to show ip count */
			if (ft_strequ(line[0], "show"))
			{
				key.address = inet_addr(line[1]);
				tofind = bsearch(&key, sarr.ip_array, sarr.array_size, sizeof(t_ip), ip_comparsion);
				if (tofind)
					dprintf(fd, "%zd\n", tofind->packets);
				else
					dprintf(fd, "Not found.\n");	
			}
			/* Response to show stat of iface */
			else if (ft_strequ(line[0], "stat"))
			{
				i = 0;
				while (i < sarr.array_size)
				{
					if (ft_strequ(sarr.devname, strtok(line[1], "\n")))
					{
						dprintf(fd, "%s\t", inet_ntoa(*(struct in_addr *)&sarr.ip_array[i].address));
						dprintf(fd, "%*zd\n", 10, sarr.ip_array[i].packets);
					}
					i++;
				}				
			}
		}
		else if (ft_elems(line) == 1)
		{
			/* Response to show all stat */
			if (ft_strequ(strtok(line[0], "\n"), "stat"))
			{
				i = 0;
				while (i < sarr.array_size)
				{
					dprintf(fd, "%s\t\t", inet_ntoa(*(struct in_addr *)&sarr.ip_array[i].address));
					dprintf(fd, "%zd\n", sarr.ip_array[i].packets);
					i++;
				}				
			}
		}
		dprintf(fd, "--------nviewer-(c)--------");
		ft_two_del(line);
	}
	close(fd);
}