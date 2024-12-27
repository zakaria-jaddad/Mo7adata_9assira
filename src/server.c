/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:47:55 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/27 00:45:30 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	signal_handler(int signal, siginfo_t *signal_info, void *template)
{
	static t_siguserinfo	g_siguserinfo;

	(void)signal_info;
	(void)template;
	if (signal != SIGUSR1 && signal != SIGUSR2)
		return ;
	// received 0
	if (signal == SIGUSR1)
		g_siguserinfo.c = g_siguserinfo.c << 1;
	// received 1
	else
		g_siguserinfo.c = (g_siguserinfo.c << 1) | 1;
	g_siguserinfo.counter++;
	if (g_siguserinfo.counter == 8)
	{
		ft_printf("%c", g_siguserinfo.c);
		g_siguserinfo.c = 0;
		g_siguserinfo.counter = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		unix_error("Can´t handle SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		unix_error("Can´t handle SIGUSR2");
	pid = getpid();
	ft_printf("Server PID: %d", pid);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
