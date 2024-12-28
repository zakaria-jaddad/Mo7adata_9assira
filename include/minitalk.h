
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:47:58 by zajaddad          #+#    #+#             */
/*   Updated: 2024/12/27 22:50:06 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_siguserinfo
{
	unsigned int	counter;
	int				c;
	pid_t			pid;
	int				is_client_currepted;
}					t_siguserinfo;

static void	unix_error(char *msg)
{
	ft_printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

#endif
