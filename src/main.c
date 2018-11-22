#include "../inc/nviewer.h"

/* Array of function's pointers initialization */
t_command g_cmds[] = {
	{"start", "packets are being sniffed from now\n on from default iface(eth0)", 
	NULL, &cmd_start},
	{"stop", "packets are not sniffed", NULL, &cmd_stop},
	{"show", "print number of packets received \nfrom ip address", "[ip] count", &cmd_show},
	{"select", "select interface for sniffing \neth0, wlan0, ethN, wlanN...", "iface [iface]",&cmd_select},
	{"stat", "show all collected statistics for particular\n interface, if iface omitted - for all interfaces.", 
	"[iface]",&cmd_stat},
	{"exit", "get the heck out of here.", NULL, &cmd_exit},
	{"--help", "show usage information.", NULL, &cmd_help}
};

/* Just because while(1) causes endless loop warning */
static int is_user_a_goat(void)
{
	return (1);
}

/*
** Dunno what was required in task, shell or just arg parse 
** so i decided to implement they both
*/

int main(int argc, char **argv)
{
	t_input *inp;
	char *buf;
	size_t size = 1024 + 1;

	if (argc == 1)
	{
		/* Shell */
		while (is_user_a_goat())
		{
			buf = (char*)malloc(sizeof(char) * size);
			printf(PROMPT);
			if (getline(&buf, &size, stdin) > 0)
			{
				inp = alloc_input(ft_strsplit(buf, ' '));
				if (inp)
					entry_switcher(inp);
			}
			free(buf);
		}
	}
	else
	{
		/* Args handle */
		inp = alloc_input(&argv[1]);
		if (inp)
			entry_switcher(inp);
	}
	return (0);
}