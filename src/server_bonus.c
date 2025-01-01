/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:42:48 by zajaddad          #+#    #+#             */
/*   Updated: 2025/01/01 15:28:14 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signal, siginfo_t *signal_info, void *template)
{
	static t_siguserinfo	siguserinfo;

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
