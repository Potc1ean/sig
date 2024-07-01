# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 04:50:58 by njeanbou          #+#    #+#              #
#    Updated: 2024/06/19 16:39:34 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(wildcard srcs/ms_utils/*.c srcs/ms_parsing/*.c srcs/ms_exec/*.c srcs/ms_cmds/*.c srcs/ms_errors/*.c srcs/ms_signal/*.c main.c)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Werror -Wextra -Wall -fsanitize=address -static-libasan

RM = rm -rf

# Colors:
GREEN   = \e[92;118m
YELLOW  = \e[93;226m
RESET   = \e[0m
CURSIVE = \e[33;3m

all: ${NAME}

${NAME}: ${OBJS}
				@printf "$(CURSIVE)- Compiling $(NAME)...$(RESET)\n"
				@${MAKE} -C ./ms_libft
				@${CC} ${CFLAGS} ${OBJS} ./ms_libft/libft.a -o ${NAME} -lreadline
				@printf "$(GREEN)- Executable $(NAME) ready.$(RESET)\n"

%.o: %.c
				@${CC} ${CFLAGS} -c $< -o $@

clean:
				@${MAKE} -C ./ms_libft fclean
				@${RM} ${OBJS}
				@printf "$(YELLOW)- Object $(NAME) removed.$(RESET)\n"

fclean: clean
				@${RM} ${NAME}
				@printf "$(YELLOW)- Executable $(NAME) removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

