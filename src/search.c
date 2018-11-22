#include "../inc/nviewer.h"

static t_ip single_ip(char *ip, char *packets)
{
	t_ip ip_sin;

	ip_sin.address = inet_addr(ip);
	ip_sin.packets = (size_t)atoi(packets);
	return (ip_sin);
}

static t_ip *alloc_ip_array(size_t *arr_size)
{
	t_ip *ip_arr = NULL;
	char buf[1024 + 1];
	FILE *fp = NULL;
	size_t arr_capac = 3;
	char **line;

	ip_arr = (t_ip*)malloc(sizeof(t_ip) * (arr_capac + 1));
	fp = fopen(LOGFILE, "r");
	if (fp)
	{
		while (fgets(buf, 1024, fp) != NULL)
		{
			if ((*arr_size) >= arr_capac)
			{
				ip_arr = realloc(ip_arr, sizeof(t_ip) * arr_capac * 2);
				arr_capac *= 2;
			}
			line = ft_strsplit(buf, ' ');
			if (line && line[1] && line[2])
			{
				ip_arr[(*arr_size)] = single_ip(line[1], line[2]);
				ft_two_del(line);
			}
			(*arr_size)++;
		}
		fclose(fp);
		return (ip_arr);
	}
	return (NULL);
}

static int ip_comparsion(const void * a, const void * b)
{
	t_ip *ip1 = (t_ip*)a;
	t_ip *ip2 = (t_ip*)b;

   return 
        ip1->address > ip2->address
        ? 1                 
        : ip1->address == ip2->address
        ? 0                 
        : -1              
        ;                   
}

void search_ip(t_input *inp)
{
	uint32_t target_ip = 0;
	t_ip *ip_arr = NULL;
	t_ip *result = NULL;
	t_ip key;
	size_t arr_size = 0;

	target_ip = inet_addr(inp->query[1]);
	ip_arr = alloc_ip_array(&arr_size);
	qsort(ip_arr, arr_size, sizeof(t_ip), ip_comparsion);
	key.address = target_ip;
	result = bsearch(&key, ip_arr, arr_size, sizeof(t_ip), ip_comparsion);
	if (result)
	{
		printf("Request Found!\n--------------\nIP\t%s\nPackets\t%ld\n", inp->query[1], result->packets);
		printf("--------------\n");
	}
	else
		printf("requested IP not found\n");
}