# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 15:39:28 by zajaddad          #+#    #+#              #
#    Updated: 2025/01/01 15:39:29 by zajaddad         ###   ########.fr        #
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
	$(MAKE) -C $(PRINTF)

libft: 
	$(MAKE) -C $(LIBFT)

libftprintf_fclean: 
	$(MAKE) -C $(PRINTF) fclean

libft_fclean: 
	$(MAKE) -C $(LIBFT) fclean

fclean: clean libftprintf_fclean libft_fclean

clean: 
	rm -f client server
	rm -f client_bonus server_bonus

re: fclean all

.PHONY: clean libftprintf_fclean libftprintf libft_fclean libft
