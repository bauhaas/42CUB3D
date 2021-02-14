/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 20:58:56 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

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
# define BLACK	0x00000000

# define CARDINAL_POINTS "NSEW"
# define TRUE 1
# define FALSE 0
# define FOV  90 * (M_PI / 180)
# define MINIMAP_SCALE 20

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
	float		mov_speed;
	float		rot_ang;
	float		rot_speed;
}				t_player;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			wid;
	int			hei;
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
	t_img		img;
	char		*name;
	int			tot_rays;
	int			hei;
	int			wid;
}				t_win;

typedef struct	s_dcast
{
	float		xstep;
	float		ystep;
	float		xinter;
	float		yinter;
	float		hit_x;
	float		hit_y;
	float		next_x;
	float		next_y;
	int			found_wall;

}				t_dcast;

typedef struct	s_ray
{
	float		ray_ang;
	float		wall_hit_x;
	float		wall_hit_y;
	t_coord		vt_hit;
	t_coord		hz_hit;
	t_line		line;
	int			found_hz_wall;
	int			found_vt_wall;
	float		distance;
	int			was_vt_hit;
	int			is_up;
	int			is_down;
	int			is_right;
	int			is_left;

	int id;
	int top_pixel;
	int bot_pixel;
}				t_ray;

typedef struct	s_text
{
	void			*ptr;
	char			*data;
	char			*name;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				wid;
	int				hei;
}				t_text;


typedef struct	s_data
{
	int				ceil;
	int				floor;
	int				cols;
	int				rows;
	int				grid_flag;
	int				res;
	double			dist_proj_plane;
	int				num_sprites;
}				t_data;

typedef struct	s_sprite
{
	t_coord		coord;
	float		distance;
	float		ang;
	int			texture;
	int			visibility;
	float 		hei;
	int 		id;
	int 		top_pixel;
	int 		bot_pixel;
	float 		first_x;
}				t_sprite;

typedef struct	s_cub3d
{
	t_img		img;
	t_win		win;
	t_player	player;
	t_ray		*rays;
	t_sprite	*sprites;
	t_text		text[5];
	t_data		data;
	char		**grid;
}				t_cub3d;

int				key_pressed(int keycode, t_cub3d *cub3d);
int				key_released(int keycode, t_player *player);

void			init_game(t_cub3d *cub3d, char *file);
void			init_texture(t_cub3d *cub3d);
void			init_grid(t_cub3d *cub3d);
void			init_player(t_player *player);
void			init_img(t_img *img, t_win *win);
void			init_win(t_win *win);
void			init_ray(t_ray *ray, float ray_ang);
t_line			init_line(t_coord a, t_coord b);
t_coord			init_coord(float a, float b);

void			render_mini_player(t_cub3d *cub3d);
void			render_mini_map(t_cub3d *cub3d);
void			render_view_line(t_line *line, t_cub3d *cub3d, int color);
void			render_mini_sprites(t_cub3d *cub3d);

void			update(t_cub3d *cub3d);
void			render(t_cub3d *cub3d);

void			my_mlx_pixel_put(t_win *win, int x, int y, int color);

void			hz_cast(t_ray *ray, t_cub3d *cub3d);
void			vt_cast(t_ray *ray, t_cub3d *cub3d);
t_ray			cast(t_ray ray, t_cub3d *cub3d);
t_ray			*cast_all_rays(t_cub3d *cub3d);

int				grid_is_wall(float x, float y, t_cub3d *cub3d);
int				grid_is_sprite(float x, float y, t_cub3d *cub3d);
float			normalize(float ray_ang);
float			p_dist(float x1, float y1, float x2, float y2);



//grid
int grid_parsing(t_cub3d *cub3d, t_list *list);
int fill_grid(t_cub3d *cub3d, t_list *list, int cols, int rows);
int grid_alloc(t_cub3d *cub3d, t_list *list);
int check_grid(t_cub3d *cub3d);
int fill_list_grid(t_cub3d *cub3d, char *line, t_list **list);
int check_surrounding(char **grid, int x, int y);
void free_grid(t_cub3d *cub3d);

//player
int check_player(t_cub3d *cub3d);

//parsing utils
int count_cols(t_list *list);
int is_num(char *num);
void free_split(char ***split);
int is_error(char *str);

//texture
int is_texture(char **line_data);
int fill_texture(t_cub3d *cub3d, char **line_data);
void free_texture(t_cub3d *cub3d);
int load_texture(t_cub3d *cub3d);

//colors
int is_rgb(char *color);
int rgb_to_hex(int r, int g, int b);
int fill_color(t_cub3d *cub3d, char **line);

//resolution
int fill_res(t_cub3d *cub3d, char **data);

//img 
void load_img(t_win *win);
void free_img(t_cub3d *cub3d);

//win
void load_win(t_win *win);
void free_win(t_cub3d *cub3d);

//sprites
int check_sprites(t_cub3d *cub3d);
void render_sprites(t_cub3d *cub3d);
int load_sprites(t_cub3d *cub3d);
void free_sprite(t_cub3d *cub3d);

int grep_color(t_text text, int x, int y);
int parsing(t_cub3d *cub3d, char *map_file);
void run_cub3d(t_cub3d *cub3d);
int end_cub3d(t_cub3d *cub3d);
#endif
