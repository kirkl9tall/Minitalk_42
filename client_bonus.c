/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:01:57 by abismail          #+#    #+#             */
/*   Updated: 2025/02/18 17:12:54 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_sign_received = 0;

void	acknowledgment_handler(int sig)
{
	(void)sig;
	g_sign_received = 1;
}

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(500);
	}
	usleep(100);
}

void	send_string(pid_t server_pid, char *str)
{
	while (*str)
	{
		send_char(server_pid, *str);
		str++;
	}
	send_char(server_pid, '\n');
	send_char(server_pid, '\0');
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	pid_t				server_pid;
	char				*c;

	if (argc != 3)
	{
		write(1, "usage   <server PID> <char >", 29);
		return (1);
	}
	sa.sa_handler = acknowledgment_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = atoi(argv[1]);
	c = argv[2];
	send_string(server_pid, c);
	while (!g_sign_received)
	{
		pause();
	}
	write(1, "Message sent and received  by server.\n", 39);
	return (0);
}
