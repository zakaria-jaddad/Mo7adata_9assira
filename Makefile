# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 15:39:28 by zajaddad          #+#    #+#              #
#    Updated: 2025/01/01 23:04:20 by zajaddad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src
LIB = lib
CFLAGS = -Wall -Werror -Wextra
INCLUDE = include/minitalk.h
MAKE = make
CC = cc

PRINTF = $(LIB)/ft_printf
LIBFT = $(LIB)/libft

OBJS = server.o
OBJC = client.o

BONUS_OBJS = bonus_server.o
BONUS_OBJC = bonus_client.o

all: libftprintf libft server client

bonus: libftprintf libft server_bonus client_bonus

%.o: $(SRC)/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lftprintf -L$(LIB)/ft_printf/ -lft -L$(LIB)/libft/ -o server 

client: $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -lftprintf -L$(LIB)/ft_printf/ -lft -L$(LIB)/libft/ -o client 

server_bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJC) -lftprintf -L$(LIB)/ft_printf/ -lft -L$(LIB)/libft/ -o server_bonus

client_bonus: $(BONUS_OBJC)
	$(CC) $(CFLAGS) $(BONUS_OBJC) -lftprintf -L$(LIB)/ft_printf/ -lft -L$(LIB)/libft/ -o client_bonus



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
	rm -f $(OBJC) $(OBJS)
	rm -f $(BONUS_OBJS) $(BONUS_OBJS)

re: fclean all

.PHONY: clean libftprintf_fclean libftprintf libft_fclean libft
