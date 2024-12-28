
SRC = src

CFLAGS = -Wall -Werror -Wextra
INCLUDE = include/minitalk.h

MAKE = make


CC = cc
AR = ar -rcs 

PRINTF = ft_printf
LIBFT = libft

all: libftprintf libft
	$(CC) $(CFLAGS) $(SRC)/client.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o client 
	$(CC) $(CFLAGS) $(SRC)/server.c -lftprintf -L./ft_printf/ -lft -L./libft/ -o server 

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
	rm -f client
	rm -f server

re: fclean all

.PHONY: clean libftprintf_fclean libftprintf libft_fclean libft
