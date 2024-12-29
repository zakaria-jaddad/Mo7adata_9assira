# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 18:43:50 by zajaddad          #+#    #+#              #
#    Updated: 2024/12/29 18:44:05 by zajaddad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = src

CFLAGS = -Wall -Werror -Wextra
INCLUDE = include/minitalk.h

MAKE = make


CC = cc

PRINTF = ft_printf
LIBFT = libft

all: libftprintf libft
	$(CC) $(CFLAGS) $(SRC)/client.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o client 
	$(CC) $(CFLAGS) $(SRC)/server.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o server 

bonus: libftprintf libft
	$(CC) $(CFLAGS) $(SRC)/client_bonus.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o client_bonus
	$(CC) $(CFLAGS) $(SRC)/server_bonus.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o server_bonus

libftprintf: 
	$(MAKE) -s -C $(PRINTF)

libft: 
	$(MAKE) -s -C $(LIBFT)

libftprintf_fclean: 
	$(MAKE) -s -C  $(PRINTF) fclean

libft_fclean: 
	$(MAKE) -s -C  $(LIBFT) fclean

fclean: clean libftprintf_fclean libft_fclean

clean: 
	rm -f client server
	rm -f client_bonus server_bonus

re: fclean all

.PHONY: clean libftprintf_fclean libftprintf libft_fclean libft
