#include  <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void send_char(pid_t server_pid , char c )
{
	int i;

	i = 8;
	while (i--)
	{
		if ((c>>i) & 1)
			kill (server_pid, SIGUSR2);
		else 
			kill (server_pid, SIGUSR1);
		usleep (100);
	}
}

void  send_string(pid_t server_pid, char *str)
{
	while (*str)
	{
		send_char(server_pid,*str);
		str++;
	}
	send_char (server_pid, '\n');
}

int main (int argc , char *argv[])
{
	if  (argc != 3)
	{
		printf("usage %s  <server PID> <char >\n",argv[0]);
		return (1);
	}

	pid_t server_pid = atoi(argv[1]);
	char *c = argv[2];

	printf ("sending the char  %s to the server\n",c);
	send_string(server_pid,c);
	return (0);
}

