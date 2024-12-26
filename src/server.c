/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:47:55 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/26 17:55:31 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static t_siginfo	g_siginfo = {.counter = 0, .c = 0};


void signal_handler(int signal, siginfo_t *signal_info, void *template)
{
        ft_printf("caught signal %d\n", signal);
        (void) signal_info;
        (void) template;
        // received 0
        if (signal == SIGUSR1)
                g_siginfo.c = g_siginfo.c << 1;
        // received 1
        else
                g_siginfo.c = (g_siginfo.c << 1) & 1;
        g_siginfo.counter++;
        if (g_siginfo.counter == 8)
        {
                ft_printf("%c", g_siginfo.c);
                g_siginfo.c = 0;
                g_siginfo.counter = 0;
        }
}


int main(void)
{
        struct sigaction sa; 


        sa.sa_sigaction = &signal_handler;

        sigemptyset(&sa.sa_mask); // what this does ?


        sa.sa_flags = SA_SIGINFO;

        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);

        pid_t pid = getpid();
        ft_printf("Server PID: %d", pid);
        while (1)
                pause();
        return EXIT_SUCCESS;
}
