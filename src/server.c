/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:47:55 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/30 00:18:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signal, siginfo_t *signal_info, void *template)
{
	static t_siguserinfo	siguserinfo;

	(void)signal_info;
	(void)template;
	if (!siguserinfo.pid)
		siguserinfo.pid = signal_info->si_pid;
	if (siguserinfo.pid != signal_info->si_pid)
		ft_bzero(&siguserinfo, sizeof(siguserinfo));
	if (signal != SIGUSR1 && signal != SIGUSR2)
		return ;
	if (signal == SIGUSR1)
		siguserinfo.c = siguserinfo.c << 1;
	else
		siguserinfo.c = (siguserinfo.c << 1) | 1;
	siguserinfo.counter++;
	if (siguserinfo.counter == 8)
	{
		ft_printf("%c", siguserinfo.c);
		siguserinfo.c = 0;
		siguserinfo.counter = 0;
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
	ft_printf("Server PID: %d\n", pid);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
