/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:47:55 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/25 19:19:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_siginfo	g_siginfo = {.counter = 0, .c = 0};

void sig_user1_handler(int signal)
{
        
}

int main(void)
{
        pid_t pid = getpid();
        ft_printf("Server PID: %d", pid);
        while (1)
                sleep(100);
        return EXIT_SUCCESS;
}
