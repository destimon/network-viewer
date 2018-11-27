#include "../inc/nviewer.h"

void search_ip(t_input *inp)
{
	uint32_t target_ip = 0;
	t_ip *ip_arr = NULL;
	t_ip *result = NULL;
	size_t arr_size = 0;
	t_ip key;
	char buf[1024];

	bzero(buf, 1024);
	int fd;
	mkfifo("fifo", 0666);
	fd = open("fifo", O_WRONLY);
	dprintf(fd, "%s %s\n", inp->query[0], inp->query[1]);
	close(fd);
	fd = open("fifo", O_RDONLY);
	read(fd, buf, sizeof(buf) + 1);
	close(fd);
	printf("IP addr: %s\n", inp->query[1]);
	printf("Packets: %s\n", buf);
}