/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:01:43 by abismail          #+#    #+#             */
/*   Updated: 2025/02/18 17:11:43 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int number)
{
	int	mod;

	if (number > 9)
	{
		mod = number % 10 + 48;
		number = number / 10;
		ft_putnbr(number);
		write(1, &mod, 1);
	}
	else if (number <= 9)
	{
		number = number + 48;
		write(1, &number, 1);
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_count;
	static char	received_char;
	static int	cmp;

	(void)context;
	if (cmp != info->si_pid)
	{
		bit_count = 0;
		received_char = 0;
	}
	cmp = info->si_pid;
	received_char <<= 1;
	if (sig == SIGUSR2)
		received_char |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (received_char != '\0')
			write(1, &received_char, 1);
		else
			kill(info->si_pid, SIGUSR2);
		bit_count = 0;
		received_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
