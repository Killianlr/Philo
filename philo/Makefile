# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 13:33:25 by kle-rest          #+#    #+#              #
#    Updated: 2023/11/23 12:16:50 by kle-rest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = main.c \
			parsing.c \
			init_val.c \
			utiles.c \
			routine.c \
			error.c \
			thread.c \
			mutex.c \

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

$(NAME) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -lpthread

all: $(NAME)

clean:
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re