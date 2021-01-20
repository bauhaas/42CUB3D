/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/20 10:31:19 by bahaas           ###   ########.fr       */
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
# define GREEN	0x0000CC00
# define RED	0x00FF0000

/*
** 	WIP: MINI_SIZE : size of cube on minimap. Need to define a width and height
**					 var equal to 1/10 of my resolution (width and height)
*/

# define TILE_SIZE	32
# define MAP_ROWS	11
# define MAP_COLS	15
# define TRUE 1
# define WIN_WID TILE_SIZE * MAP_COLS
# define WIN_HEI TILE_SIZE * MAP_ROWS
# define FOV  60 * (M_PI / 180)
# define WALL_STIP_WIDTH 1
# define NUM_RAYS WIN_WID / WALL_STIP_WIDTH

typedef struct	s_coord
{
	float		x;
	float		y;
}				t_coord;

typedef struct	s_player
{
	t_coord		pos;
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

typedef struct	s_line
{
	t_coord		start;
	t_coord		end;
}				t_line;

typedef struct	s_win
{
	void		*mlx_p;
	void		*win_p;
}				t_win;

typedef struct	s_ray
{
	float		ray_ang;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int		facing_up;
	int		facing_down;
	int		facing_right;
	int		facing_left;
}				t_ray;

typedef struct	s_cub3d
{
	t_map		map;
	t_img		img;
	t_win		win;
	t_player	player;
	t_ray		ray;
}				t_cub3d;

int				key_pressed(int keycode, t_cub3d *cub3d);
int				key_released(int keycode, t_player *player);

void			init_player(t_player *player);
void			init_map(t_map *map);
void			init_img(t_img *img, t_win *win);
void			init_win(t_win *win);
void			init_ray(t_ray *ray, float ray_ang);

void			render_player(t_cub3d *cub3d);
void			render_minimap(t_cub3d *cub3d);
void			render_minimap_square(int x, int y, int size, t_cub3d *cub3d);
//void			render_minimap_square(float x, float y, int size, t_cub3d *cub3d);
void			render_view_line(t_line *line, t_cub3d *cub3d, int color);
void			render_ray(t_cub3d *cub3d, t_ray rays);

void			update(t_cub3d *cub3d);
void			render(t_cub3d *cub3d);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);


#endif
