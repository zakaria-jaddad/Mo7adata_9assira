/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:56:03 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/27 22:50:54 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>

void	handle_signal(int signal)
{
	(void) signal;
	exit(EXIT_FAILURE);
}

void	send_bits(pid_t serverpid, char c)
{
	int	i;

	i = 128;
	while (i)
	{
		if (c & i)
		{
			if (kill(serverpid, SIGUSR2) == -1)
				unix_error("Kill error");
		}
		else
		{
			if (kill(serverpid, SIGUSR1) == -1)
				unix_error("Kill error");
		}
		usleep(100);
		i = i >> 1;
	}
}

void	send_buffer(pid_t serverpid, char *buffer)
{
	if (buffer == NULL)
		return ;
	while (*buffer)
		send_bits(serverpid, *buffer++);
}

void	initialize_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGKILL, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	char	*buffer;

	if (argc != 3)
		unix_error("./prog PID \"string\"");
	/* initialize_signal_handlers(); */
	
	buffer = argv[2];
	serverpid = ft_atoi(argv[1]);
	if (serverpid < 1)
		unix_error("Unvalid PID");
	send_buffer(serverpid, buffer);
	return (0);
}
