# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 12:08:52 by bahaas            #+#    #+#              #
#    Updated: 2021/02/12 16:13:39 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCS	= srcs/test.c srcs/cast_hz.c srcs/cast_vt.c srcs/cast_ray.c srcs/minimap.c srcs/utils_raycasting.c srcs/key_events.c srcs/parsing.c \
		  srcs/player.c srcs/texture.c srcs/grid.c srcs/utils_parsing.c srcs/grid_parsing.c srcs/colors.c srcs/resolution.c \
		  srcs/images.c srcs/window.c srcs/utils_init.c srcs/main.c
#SRCS	= srcs/parsing.c \
		  srcs/player.c srcs/texture.c srcs/grid.c srcs/utils_parsing.c srcs/grid_parsing.c srcs/colors.c srcs/resolution.c \
		  srcs/images.c srcs/window.c srcs/utils_init.c
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
			make clean -C ${LIB_D}
			${RM} ${OBJS}

fclean:		clean
			make fclean -C ${LIB_D}
			${RM} ${NAME}

re:			fclean all

run:		all
			./${NAME}

.PHONY:		all clean fclean re run
