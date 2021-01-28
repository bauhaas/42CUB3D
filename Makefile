# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 12:08:52 by bahaas            #+#    #+#              #
#    Updated: 2021/01/28 00:18:08 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCS	= srcs/test.c srcs/init.c srcs/init2.c srcs/cast_hz.c srcs/cast_vt.c srcs/cast_ray.c srcs/minimap.c srcs/utils_raycasting.c srcs/key_events.c srcs/parsing.c
CC		= gcc
#CFLAGS	= -Wextra -Werror -Wall
CFLAGS	=  
RM		= rm -f
LIB_D	= ./libft
MLX_D	= ./minilibx
HEADER	= -I /includes
OBJS	= ${SRCS:.c=.o}

.c.o:
			${CC} ${HEADER} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			make -C ${LIB_D}
			${CC} ${HEADER} ${OBJS} -o ${NAME} -L ${LIB_D} -lft -L ${MLX_D} -lmlx -lXext -lX11 -lm

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

run:		all
			./${NAME}

.PHONY:		all clean fclean re run
