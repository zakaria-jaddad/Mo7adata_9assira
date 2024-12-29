/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:41:27 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/29 19:45:28 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

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
	ft_printf("Message Sent Successfully\n");
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	char	*buffer;
	if (argc != 3)
		unix_error("./prog PID \"string\"");
	buffer = argv[2];
	serverpid = ft_atoi(argv[1]);
	if (serverpid < 1)
		unix_error("Invalid PID");
	send_buffer(serverpid, buffer);
	return (0);
}
