# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorin <clorin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 09:43:04 by clorin            #+#    #+#              #
#    Updated: 2021/01/13 11:59:33 by clorin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

#	Sources

SRC			=	srcs/main.c srcs/images.c srcs/map.c srcs/player.c srcs/window.c srcs/tools.c srcs/setup.c \
				srcs/parse.c srcs/graphics.c srcs/game.c srcs/check_map.c srcs/keyboard.c srcs/render.c \
				srcs/map_utils.c srcs/raycasting.c srcs/textures.c \
				srcs/point.c srcs/facing.c srcs/inters_vert.c srcs/inters_horz.c srcs/free_functions.c \
				srcs/check_sprites.c srcs/error.c srcs/sprites.c srcs/textures_utils.c srcs/sprites_utils.c \
				srcs/bmp.c

B_SRC		=	bonus/main_bonus.c bonus/images_bonus.c bonus/map_bonus.c bonus/player_bonus.c bonus/window_bonus.c bonus/tools_bonus.c bonus/setup_bonus.c \
				bonus/parse_bonus.c bonus/graphics_bonus.c bonus/game_bonus.c bonus/check_map_bonus.c bonus/keyboard_bonus.c bonus/render_bonus.c \
				bonus/map_utils_bonus.c bonus/raycasting_bonus.c bonus/textures_bonus.c bonus/mini_map_bonus.c \
				bonus/point_bonus.c bonus/facing_bonus.c bonus/inters_vert_bonus.c bonus/inters_horz_bonus.c bonus/free_functions_bonus.c \
				bonus/check_sprites_bonus.c bonus/error_bonus.c bonus/sprites_bonus.c bonus/textures_utils_bonus.c bonus/sprites_utils_bonus.c \
				bonus/bmp_bonus.c bonus/shadow_bonus.c
				#bonus/play_sound.c

CC			=	clang

FLAGS		= -Werror -Wextra -Wall

HEADER		= -I includes/

B_HEADER	= -I bonus/includes/

OBJ 		= $(SRC:.c=.o)

B_OBJ		= $(B_SRC:.c=.o)

all : $(NAME)

.c.o:
			@${CC} ${FLAGS} ${HEADER} -c $< -o ${<:.c=.o}
			@echo "compilation : "$< "\033[32mok\033[0m"

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) -L libft/ -lft -L./minilibx -lmlx -lXext -lX11 -lm
	@echo "création de Cub3D : \033[32mok\033[0m"

clean:
	rm -rf $(OBJ) $(B_OBJ)
	rm -rf save.bmp

fclean: clean
	@make fclean -C libft/
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

bonus: fclean $(B_OBJ)
		@make -C libft/
		@echo "\n\033[0;32mCompiling bonus..."
		@$(CC) -o $(NAME) $(FLAGS) $(B_HEADER) $(B_OBJ) -L libft/ -lft -L./minilibx -lmlx -lXext -lX11 -lm -lpthread -D_REENTRANT
		@echo "\033[0m"
test:	
	./$(NAME) maps/map.cub
bmp:
	./$(NAME) maps/map.cub --save

.PHONY: all clean fclean re bonus test bmp
