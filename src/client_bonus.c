/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:41:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/01/01 15:28:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	confirme(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message Successfully Sent To Server\n");
	exit(EXIT_SUCCESS);
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
	send_bits(serverpid, '\0');
}

int	check_pid(char *s)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	char	*buffer;

	if (argc != 3)
		unix_error("./prog <PID> \"string\"");
	buffer = argv[2];
	if (!check_pid(argv[1]))
		unix_error("Invalid PID");
	serverpid = ft_atoi(argv[1]);
	signal(SIGUSR2, confirme);
	if (serverpid < 1)
		unix_error("Invalid PID");
	send_buffer(serverpid, buffer);
	pause();
	return (EXIT_SUCCESS);
}
