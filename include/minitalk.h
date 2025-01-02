/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:26:57 by zajaddad          #+#    #+#             */
/*   Updated: 2025/01/02 18:35:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_siguserinfo
{
	int				byte_counter;
	unsigned char	utf8_string[5];
	int				byte_index;
	unsigned int	counter;
	int				c;
	pid_t			pid;
}					t_siguserinfo;

static void	unix_error(char *msg)
{
	ft_printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

#endif
