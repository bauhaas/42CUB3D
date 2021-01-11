# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 12:08:52 by bahaas            #+#    #+#              #
#    Updated: 2021/01/11 12:31:01 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CC		= gcc
CFLAGS	= -Wextra -Werror -Wall
RM		= rm -f
LIB_D	= libft
MLX_D	= minilibx
OBJS	= ${addprefix srcs/,${SRCS:.c=.o}}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			make -C ${LIB_D}
			make -C ${MLX_D}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
