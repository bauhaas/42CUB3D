# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 12:08:52 by bahaas            #+#    #+#              #
#    Updated: 2021/02/18 23:30:28 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCS	= srcs/render.c srcs/cast_hz.c srcs/cast_vt.c srcs/cast_ray.c \
		  srcs/minimap.c srcs/utils.c srcs/key_events.c srcs/parsing.c \
		  srcs/player.c srcs/texture.c srcs/grid.c srcs/utils_parsing.c \
		  srcs/grid_parsing.c srcs/colors.c srcs/resolution.c srcs/images.c \
		  srcs/window.c srcs/utils_init.c srcs/main.c srcs/sprites.c \
		  srcs/utils_sprites.c srcs/utils_render.c srcs/render_sprites.c \
		  srcs/save.c srcs/healthbar.c

SRCS_BONUS	= bonus/render_bonus.c bonus/cast_hz_bonus.c bonus/cast_vt_bonus.c \
			  bonus/cast_ray_bonus.c bonus/minimap_bonus.c \
			  bonus/utils_bonus.c bonus/key_events_bonus.c \
			  bonus/parsing_bonus.c bonus/player_bonus.c bonus/texture_bonus.c \
			  bonus/grid_bonus.c bonus/utils_parsing_bonus.c \
			  bonus/grid_parsing_bonus.c bonus/colors_bonus.c \
			  bonus/resolution_bonus.c bonus/images_bonus.c \
			  bonus/window_bonus.c bonus/utils_init_bonus.c bonus/main_bonus.c \
			  bonus/sprites_bonus.c bonus/utils_sprites_bonus.c \
			  bonus/utils_render_bonus.c bonus/render_sprites_bonus.c

CC		= gcc
CFLAGS	= -Wextra -Werror -Wall
RM		= rm -f
LIB_D	= ./libft
MLX_D	= ./minilibx
HEADER	= -I /includes
HEADER_BONUS	= -I /includes
OBJS	= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

.c.o:
			${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			make -C ${LIB_D}
			${CC} ${HEADER} -pg ${OBJS} -o ${NAME} -O -O3 -L ${LIB_D} -lft -L ${MLX_D} -lmlx -lXext -lX11 -lm

all:		${NAME}

clean:
			make clean -C ${LIB_D}
			${RM} ${OBJS}

fclean:		clean
			make fclean -C ${LIB_D}
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS_BONUS}
			make -C ${LIB_D}
			${CC} ${HEADER} ${OBJS_BONUS} -o ${NAME} -L ${LIB_D} -lft -L ${MLX_D} -lmlx -lXext -lX11 -lm

.PHONY:		all clean fclean re run
