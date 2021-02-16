/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/16 02:54:06 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"


//#include "sprites.h"
/*
** KEY EVENTS
** to find keycode of each key, execute 'xev' in terminal and press key wanted
*/

# define KEY_Z		122
# define KEY_Q		113
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_DOWN	65364
# define KEY_RIGHT	65363
# define KEY_ESC	65307

/*
** COLORS
** https://www.rapidtables.com/web/color/RGB_Color.html#color-table
*/

# define GRAY	0x00C7C9D1
# define V_GRAY	0x00E1E3E8
# define D_GRAY	0x00818591
# define BLUE	0x000000FF
# define WHITE	0x00FFFFFF
# define GREEN	0x0074B44A
# define RED	0x00FF0000
# define BLACK	0x00000000

# define CARDINAL_POINTS "NSEW"
# define TRUE 1
# define FALSE 0
# define FOV  90 * (M_PI / 180)
# define MINIMAP_SCALE 15

typedef struct	s_pos
{
	float		x;
	float		y;
}				t_pos;

typedef struct	s_player
{
	int			lateral_d;
	float		mov_speed;
	float		rot_speed;
	float		rot_ang;
	int			walk_d;
	int			radius;
	int			turn_d;
	int			rot_d;
	t_pos		pos;
}				t_player;

typedef struct	s_img
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	void		*img;
	int			wid;
	int			hei;
}				t_img;

typedef struct	s_line
{
	t_pos		start;
	t_pos		end;
}				t_line;

typedef struct	s_win
{
	int			tot_rays;
	void		*mlx_p;
	void		*win_p;
	char		*name;
	t_img		img;
	int			hei;
	int			wid;
}				t_win;

typedef struct	s_dcast
{
	int			found_wall;
	float		xinter;
	float		yinter;
	float		next_x;
	float		next_y;
	float		xstep;
	float		ystep;
	float		hit_x;
	float		hit_y;

}				t_dcast;

typedef struct	s_ray
{
	int			found_hz_wall;
	int			found_vt_wall;
	float		wall_hit_x;
	float		wall_hit_y;
	int			was_vt_hit;
	int			is_right;
	int			is_left;
	int			is_down;
	int			is_up;
	float		ray_ang;
	int			top_px;
	int			bot_px;
	t_pos		vt_hit;
	t_pos		hz_hit;
	t_line		line;
	float		dist;
	int			id;
}				t_ray;

typedef struct	s_text
{
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*name;
	char			*data;
	void			*ptr;
	int				wid;
	int				hei;
}				t_text;


typedef struct	s_data
{
	double			dist_proj_plane;
	int				grid_flag;
	int				num_sprt;
	int				floor;
	int				ceil;
	int				cols;
	int				rows;
	int				res;
}				t_data;


typedef struct	s_sprt
{
	int			visibility;
	float 		first_x;
	int			texture;
	int 		top_px;
	int 		bot_px;
	float		dist;
	t_pos		pos;
	float		ang;
	float 		hei;
	int 		id;
}				t_sprt;

typedef struct	s_health
{
	t_pos		start;
	t_pos		end;
}				t_health;

typedef struct	s_cub
{
	t_health	healthbar;
	t_text		text[5];
	t_player	player;
	char		**grid;
	t_ray		*rays;
	t_sprt		*sprt;
	t_data		data;
	t_img		img;
	t_win		win;
	int			save;
}				t_cub;

void	init_healthbar(t_cub *cub);
void	render_health_text(t_cub *cub);
void	render_healthbar(t_cub *cub);
void		rect(t_cub *cub, t_pos a, t_pos b, int color);
int save_bmp(t_cub *cub);
void	load_cub(t_cub *cub, char *map);
int		cub_ext(char *map_file);


int				key_pressed(int key, t_cub *cub);
int				key_released(int key, t_player *player);

void			init_game(t_cub *cub, char *file);
void			init_texture(t_cub *cub);
void			init_grid(t_cub *cub);
void			init_player(t_player *player);
void			init_img(t_img *img);
void			init_win(t_win *win);
void			init_ray(t_ray *ray, float ray_ang);
t_line			init_line(t_pos a, t_pos b);
t_pos			init_pos(float a, float b);

void			render_mini_player(t_cub *cub);
void			render_mini_map(t_cub *cub);
void			render_mini_sprt(t_cub *cub);

void			update(t_cub *cub, t_player *player);
int				render(t_cub *cub);

void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
void			square(t_pos pos, int size, t_cub *cub, int color);
void			render_line(t_line *line, t_cub *cub, int color);

void			hz_cast(t_ray *ray, t_cub *cub, int i);
void			vt_cast(t_ray *ray, t_cub *cub, int i);
t_ray			cast(t_ray ray, t_cub *cub);
void			cast_all_rays(t_cub *cub);

int				grid_is_wall(float x, float y, t_cub *cub);
int				grid_is_sprt(float x, float y, t_cub *cub);
float			normalize(float ray_ang);
float			p_dist(float x1, float y1, float x2, float y2);



//grid
int grid_parsing(t_cub *cub, t_list *list);
int fill_grid(t_cub *cub, t_list *list);
int grid_alloc(t_cub *cub, t_list *list);
int check_grid(t_cub *cub);
int fill_list_grid(char *line, t_list **list);
int check_surrounding(char **grid, int x, int y);
void free_grid(t_cub *cub);

//player
int check_player(t_cub *cub);

//parsing utils
int count_cols(t_list *list);
int is_num(char *num);
void free_split(char ***split);
int is_error(char *str);

//texture
int is_texture(char **line_data);
int fill_texture(t_cub *cub, char **line_data);
void free_texture(t_cub *cub);
int load_texture(t_cub *cub);

//colors
int is_rgb(char *color);
int rgb_to_hex(int r, int g, int b);
int fill_color(t_cub *cub, char **line);

//resolution
int fill_res(t_cub *cub, char **data);

//img 
void load_img(t_win *win);
void free_img(t_cub *cub);

//win
void load_win(t_win *win);
void free_win(t_cub *cub);

//sprt
int check_sprt(t_cub *cub);
int load_sprt(t_cub *cub);
void free_sprt(t_cub *cub);
void	sort_sprt(t_cub *cub);
void	fill_sprt(t_cub *cub, int i);
void	draw_sprt(t_cub *cub, t_sprt sprt, t_pos pos, t_pos offset);
void	sprt_data(t_cub *cub);
void	render_sprt(t_cub *cub);
void			is_visible(t_cub *cub, int i);
float			find_angle(t_cub *cub, int i);

int grep_color(t_text text, int x, int y);
int parsing(t_cub *cub, char *map_file);
void run_cub(t_cub *cub);
int end_cub(t_cub *cub);
#endif
