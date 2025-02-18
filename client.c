/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:01:48 by abismail          #+#    #+#             */
/*   Updated: 2025/02/18 17:08:35 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	pid_t	server_pid;
	char	*c;

	c = argv[2];
	server_pid = atoi(argv[1]);
	if (argc != 3)
	{
		write(1, "usage .  <server PID> <char >", 29);
		return (1);
	}
	send_string(server_pid, c);
	return (0);
}
