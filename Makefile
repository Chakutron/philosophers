# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 15:15:55 by mchiboub          #+#    #+#              #
#    Updated: 2023/07/02 19:34:47 by mchiboub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS =	check_dead.c	\
		check_philo.c	\
		create_philo.c	\
		end.c			\
		init.c			\
		loop_philo.c	\
		philo.c			\
		print.c			\
		timer.c			\
		utils.c

OBJS = ${SRCS:.c=.o}

GREEN = \033[0;32m
NC = \033[0m

all: ${NAME}

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		@echo "Generating ${GREEN}${NAME}${NC} executable.."
		@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
		@echo "Deleting object files.."
		@rm -f ${OBJS}

fclean: clean
		@echo "Deleting executable files.."
		@rm -f ${NAME}

re: fclean all
