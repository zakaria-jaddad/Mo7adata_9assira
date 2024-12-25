
SRC = src

CFLAGS = -Wall -Werror -Wextra
INCLUDE = include/minitalk.h

MAKE = make


CC = cc
AR = ar -rcs 

PRINTF = ft_printf

all: libftprintf
	$(CC) $(CFLAGS) $(SRC)/client.c -lftprintf -L./ft_printf/ -o client 
	$(CC) $(CFLAGS) $(SRC)/server.c -lftprintf -L./ft_printf/ -o server 

libftprintf: 
	$(MAKE) -s -C $(PRINTF)

libftprintf_fclean: 
	$(MAKE) -s -C  $(PRINTF) fclean

fclean: clean libftprintf_fclean

clean: 
	rm -f client
	rm -f server

re: fclean all

.PHONY: clean libftprintf_fclean libftprintf
