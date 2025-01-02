/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:42:48 by zajaddad          #+#    #+#             */
/*   Updated: 2025/01/02 18:35:31 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <bits/types/siginfo_t.h>

int	get_bytes_count(int c)
{
	if (c < 0x80)
		return (1);
	else if ((c & 0xe0) == 0xc0)
		return (2);
	else if ((c & 0xf0) == 0xe0)
		return (3);
	return (4);
}

void	parse_bit(int signal, t_siguserinfo *siguserinfo)
{
	if (signal == SIGUSR1)
		siguserinfo->c = siguserinfo->c << 1;
	else
		siguserinfo->c = (siguserinfo->c << 1) | 1;
}

void	check_signal_pid(t_siguserinfo *siguserinfo, siginfo_t *signal_info)
{
	if (!siguserinfo->pid)
		siguserinfo->pid = signal_info->si_pid;
	if (siguserinfo->pid != signal_info->si_pid)
		ft_bzero(siguserinfo, sizeof(*siguserinfo));
}

void	signal_handler(int signal, siginfo_t *signal_info, void *context)
{
	static t_siguserinfo	siguserinfo;

	(void)context;
	check_signal_pid(&siguserinfo, signal_info);
	parse_bit(signal, &siguserinfo);
	siguserinfo.counter++;
	if (siguserinfo.counter == 8)
	{
		if (siguserinfo.byte_index == 0)
			siguserinfo.byte_counter = get_bytes_count(siguserinfo.c);
		if (--siguserinfo.byte_counter == 0)
		{
			siguserinfo.utf8_string[siguserinfo.byte_index] = siguserinfo.c;
			siguserinfo.utf8_string[++siguserinfo.byte_index] = 0;
			ft_printf("%s", siguserinfo.utf8_string);
			siguserinfo.byte_index = 0;
		}
		else
			siguserinfo.utf8_string[siguserinfo.byte_index++] = siguserinfo.c;
		if (siguserinfo.c == '\0')
			if (kill(signal_info->si_pid, SIGUSR2) == -1)
				unix_error("Unable To Send Aknowledgement To Client\n");
		siguserinfo.c = 0;
		siguserinfo.counter = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		unix_error("Can´t handle SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		unix_error("Can´t handle SIGUSR2");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
