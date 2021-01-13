/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/13 02:36:30 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"

/*
** KEY EVENTS
** to find keycode of each key, execute 'xev' in terminal and press key wanted
*/

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		111
# define KEY_LEFT	113
# define KEY_DOWN	116
# define KEY_RIGHT	114

/*
** COLORS
** https://www.rapidtables.com/web/color/RGB_Color.html#color-table
*/

# define GRAY	0x00808080
# define BLUE	0x000000FF
# define WHITE	0x00FFFFFF

/*
** 	WIP: MINI_SIZE : size of cube on minimap. Need to define a width and height
**					 var equal to 1/10 of my resolution (width and height)
*/

# define MINI_SIZE	20
# define MAP_ROWS	10
# define MAP_COLS	10

typedef struct	s_win
{
	void		*mlx_p;
	void		*win_p;
}				t_win;

typedef struct	s_player
{
	int			x;
	int			y;
	int			radius;
	int			turn_d;
	int			rot_d;
	int			walk_d;
	int			mov_speed;
	float		rot_ang;
	float		rot_speed;
}				t_player;

typedef struct	s_map
{
	int			cols;
	int			rows;
}				t_map;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_cub3d
{
	t_map		map;
	t_img		img;
	t_win		win;
	t_player	player;
}				t_cub3d;

int				key_pressed(int keycode, t_player *player);
int				key_released(int keycode, t_player *player);

void			init_player(t_player *player);
void			init_map(t_map *map);
void			init_img(t_img *img, t_win *win);
void			init_win(t_win *win);

void			render_player(t_img *img, t_player *player);
void			render_minimap();
void			render_minimap_wall_square(int x, int y, int size, t_img *img);
void			render_view_line(int x, int y, int size, t_img *img);

#endif
