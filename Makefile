# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 14:40:58 by fleitz            #+#    #+#              #
#    Updated: 2022/03/18 13:28:58 by fleitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END=$'\033[0m
_GREEN=$'\033[1;32m
_YELLOW=$'\033[1;33m
_ORANGE=$'\033[38;2;255;165;0m

NAME		= so_long

SRCS		= srcs/main.c			\
			srcs/show.c				\
			srcs/events.c			\
			srcs/parsing_map.c		\
			srcs/clean.c			\
			srcs/images.c			\
			srcs/protect.c			\
			srcs/items.c			\
			srcs/exit.c				\
			srcs/end.c				\
			srcs/kill.c				\
			
OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

LIB			= libft/libft.a

MLX			= ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a

all:		${NAME}

${NAME}:	${OBJS}
			@echo "${_ORANGE}Objects so_long created${_END}"
			@make -C libft
			@make -C minilibx-linux
			@${CC} ${CFLAGS} -L /usr/lib ${OBJS} ${LIB} ${MLX} -lXext -lX11 -lm -lz -o ${NAME}
			@echo "${_GREEN}SO_LONG compiled succesfully !${_END}"

%.o: %.c
			@${CC} ${CFLAGS} -I /usr/include -Imlx_linux -O3 -c $< -o $@

clean:
			@make clean -C libft
			@make clean -C minilibx-linux
			@rm -f ${OBJS}
			@echo "${_YELLOW}Objects cleaned !${_END}"

fclean:		clean
			@rm -f ${NAME} ${LIB}
			@echo "${_YELLOW}${NAME} cleaned !${_END}"

re:			fclean all

.PHONY:		clean fclean re all
