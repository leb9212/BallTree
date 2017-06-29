# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elee <elee@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/28 10:43:56 by elee              #+#    #+#              #
#    Updated: 2017/06/28 20:56:42 by elee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = balltree_knn

CC = gcc

CFLAGS = -Wall -Werror

SRCS = ball.c metrics.c neighbors_heap.c main.c json.c

OBJS = $(SRCS:.c=.o)

INCS = includes/

all: $(NAME)

$(NAME):
	mkdir -p build/
	$(CC) $(CFLAGS) -c $(addprefix srcs/, $(SRCS)) -I$(INCS)
	mv $(OBJS) build/
	$(CC) $(CFLAGS) $(addprefix build/, $(OBJS)) -o $(NAME) -lm

clean:
	/bin/rm -rf build

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
