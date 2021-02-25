/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 14:25:24 by bahaas           ###   ########.fr       */
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
# define FOV  85 * (M_PI / 180)
# define MINIMAP_SCALE 10

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
	int			texture;
	int 		top_px;
	int 		bot_px;
	float		dist;
	t_pos		pos;
	float		ang;
	float 		hei;
	int 		id;
	float 		pos_x;
}				t_sprt;

typedef struct	s_health
{
	t_pos		start;
	t_pos		end;
}				t_health;

typedef struct	s_bmp
{
	char		*signature;
	int			size_file;
	int			reserved;
	int			data_offset;
	int			size_infoheader;
	int			wid;
	int			hei;
	int			planes;
	int			bpp;
	int			*addr;
	double		padding_trash;
}				t_bmp;

typedef struct	s_cub
{
	t_health	healthbar;
	t_text		text[5];
	t_player	player;
	char		**grid;
	t_ray		*rays;
	t_sprt		*sprt;
	t_data		data;
	int			save;
	t_win		win;
	int			ray_load;
	int			sprt_load;
}				t_cub;

//save.c
int				save_bmp(t_cub *cub);

//key_events.c
int				key_pressed(int key, t_cub *cub);
int				key_released(int key, t_player *player);


//utils_init.c
void			init_ray(t_ray *ray, float ray_ang);
t_line			init_line(t_pos a, t_pos b);
t_pos			init_pos(float a, float b);

//parsing.c
int				fill_list_grid(t_cub *cub, char *line, t_list **list);
int				line_data(t_cub *cub, char *line, t_list **list);
int				last_load(t_cub *cub);
int				check_missing(t_cub *cub);
int				parsing(t_cub *cub, char *map_file, t_list **list);

//render.c
int				render(t_cub *cub);
void			render_3d(t_cub *cub);
void			render_wall(t_cub *cub, int i, float wall_hei);
void			render_ceil(t_cub *cub, t_ray rays, int i);
void			render_floor(t_cub *cub, t_ray rays, int i);

//utils_render.c
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
void			rect(t_cub *cub, t_pos a, t_pos b, int color);
void			square(t_pos pos, int size, t_cub *cub, int color);
void			render_line(t_line *line, t_cub *cub, int color);

//utils.c
int				grid_is_wall(float x, float y, t_cub *cub);
float			normalize(float ray_ang);
float			p_dist(float x1, float y1, float x2, float y2);
int				grep_color(t_text text, int x, int y);

//cast_*.c
void			cast_all_rays(t_cub *cub);
t_ray			cast(t_ray ray, t_cub *cub);
void			select_texture(t_ray *rays, float hz_dist, float vt_dist);
float			find_ray_dist(float hz_dist, float vt_dist);
float			find_ray_hit(float hz_dist, float vt_dist, float hz_hit, float vt_hit);
void			hz_cast(t_ray *ray, t_cub *cub, int i);
void			vt_cast(t_ray *ray, t_cub *cub, int i);
t_dcast 		fill_hz_data(t_cub *cub, t_ray *ray);
t_dcast			fill_vt_data(t_cub *cub, t_ray *ray);

//*grid*.c
void			init_grid(t_cub *cub);
void			free_grid(t_cub *cub);
int				fill_grid(t_cub *cub, t_list *list);
int				grid_alloc(t_cub *cub, t_list *list);
int				grid_parsing(t_cub *cub, t_list *list);

int				check_surrounding(char **grid, int x, int y);
int				is_grid(t_cub *cub, int rows, int y, int len);
int				check_grid(t_cub *cub);

//minimap.c
void			render_mini_player(t_cub *cub);
void			render_mini_map(t_cub *cub);
void			render_mini_sprt(t_cub *cub);

//player.c
void			init_player(t_player *player);
void			update(t_cub *cub, t_player *player);
void			pos_player(t_player *player, int x, int y, char orientation);
int				check_player(t_cub *cub);

//utils_parsing.c
int				count_cols(t_list *list);
int				is_num(char *num);
int				free_split(char ***split, int ret);
int				is_error(char *str);
int				cub_ext(char *map_file);

//texture.c
void			init_texture(t_cub *cub);
void			free_texture(t_cub *cub);
int				load_texture(t_cub *cub);
int				is_texture(char **line_data);
int				fill_texture(t_cub *cub, char **line_data);

//colors.c
int				is_rgb(char *color);
int				rgb_value(int r, int g, int b);
int				fill_ceil(t_cub *cub, int hex_color);
int				fill_floor(t_cub *cub, int hex_color);
int				check_format(char *line, int total);
int				fill_color(t_cub *cub, char *line);

//resolution.c
void			check_res(t_cub *cub);
void			win_size(t_cub *cub, char **data);
int				num_args(char **data, int i, int tot);
int				fill_res(t_cub *cub, char **data);

//healthbar.c
void			init_healthbar(t_cub *cub);
void			render_healthbar_text(t_cub *cub);
void			render_healthbar(t_cub *cub);

//images.c
void			init_img(t_img *img);
void			load_img(t_win *win);
void			free_img(t_cub *cub);

//window.c
void			init_win(t_win *win);
void			load_win(t_win *win);
void			free_win(t_cub *cub);

//*sprites*.c
void			init_sprt(t_cub *cub, int i, int x, int y);
int				load_sprt(t_cub *cub);
void 			free_sprt(t_cub *cub);
int				check_sprt(t_cub *cub);
void			num_sprt(t_cub *cub);

void			fill_sprt(t_cub *cub, int i);
void			sprt_color(t_cub *cub, t_pos text, t_pos pos, int i);
void			sprt_display(t_cub *cub, int i);
void			fill_sprt_data(t_cub *cub);
void			render_sprt(t_cub *cub);

void			is_visible(t_cub *cub, int i);
float			find_angle(t_cub *cub, int i);
void			sort_sprt(t_cub *cub);

//main.c
void			init_cub(t_cub *cub, char *map);
void			load_cub(t_cub *cub, char *map);
void			run_cub(t_cub *cub);
int				end_cub(t_cub *cub);

#endif
