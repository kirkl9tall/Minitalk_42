#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int bit_count = 0;
char  received_char = 0;

void signal_handler (int sig)
{
	received_char <<= 1;
	if (sig == SIGUSR2)
		received_char |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1,&received_char,1);
		bit_count = 0;
		received_char = 0;
	}
}

int main ()
{
	printf(" Server side ! PID = [%d] \n",getpid());
	//register signal handler !
	
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset (&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);
	while (1)
	{
		pause(); //wait for signal 
	}
	return (0);
}
