/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/27 15:30:43 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t* color_buffer = NULL;

void update(t_cub3d *cub3d)
{
	float mov_step;
	float new_player_x;
	float new_player_y;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	//for sprite if too much rotation
	cub3d->player.rot_ang = normalize(cub3d->player.rot_ang);

	//move player dot
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	new_player_x = cub3d->player.pos.x + cos(cub3d->player.rot_ang) * mov_step;
	new_player_y = cub3d->player.pos.y + sin(cub3d->player.rot_ang) * mov_step;

	if(!grid_is_wall(new_player_x, new_player_y, cub3d))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
}

void		rect(float x, float y, float x2, float y2, t_cub3d *cub3d, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j < x2)
	{
		i = 0;
		while (i < y2)
		{
			my_mlx_pixel_put(&cub3d->img, x + j, y + i, color);
			i++;
		}
		j++;
	}
}
/*
void				init_texture(t_cub3d cub3d)
{

	//cub3d.text->addr = NULL;
	//cub3d.text->data = NULL;
	//cub3d.text->file = NULL;
//	cub3d.text->width = 0;
//	cub3d.text->height = 0;
//	cub3d.text->bits_per_pixel = 0;
//	cub3d.text->line_length = 0;
//	cub3d.text->endian = 0;
}

static int			valid_texture(t_cub3d *cub3d, char *file, int nb)
{
	int				fd;

	fd = open(file, O_RDONLY);
	close(fd);
	cub3d->text->file = strdup(file);
	return (TRUE);
}

int					load_textures(t_cub3d *cub3d)
{
	cub3d->text->addr = mlx_xpm_file_to_image(cub3d->win.mlx_p,
			cub3d->text->file, &cub3d->text->width, &cub3d->text->height);
	if (cub3d->text->addr)
	{
		cub3d->text->data = mlx_get_data_addr(cub3d->text->addr,
				&cub3d->text->bits_per_pixel,
				&cub3d->text->line_length, &cub3d->text->endian);
	}
	else
		return (FALSE);
	return (TRUE);
}

int		get_texture_color(t_cub3d *cub3d, int x, int y)
{
	char	*dst;

	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (y > cub3d->text->height)
		y = cub3d->text->height;
	if (x > cub3d->text->width)
		x = cub3d->text->width;
	dst = cub3d->text->addr + (y * cub3d->text->line_length + x * cub3d->text->bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}
*/
void	render_3d_walls(t_ray *rays, t_cub3d *cub3d)
{
	int		i;
	int		wall_strip_height;
	float	perp_distance;
	float	ray_distance;
	int top_pixel;
	int bot_pixel;
	t_line line;
	t_coord coord;
	t_coord coord2;


	i = 0;
	while(i < NUM_RAYS)
	{
		top_pixel = (WIN_HEI / 2) - (wall_strip_height / 2);
		top_pixel = top_pixel < 0 ? 0 : top_pixel;
		bot_pixel = (WIN_HEI / 2) + (wall_strip_height / 2);
		bot_pixel = bot_pixel > WIN_HEI ? WIN_HEI : bot_pixel;
		ray_distance = rays[i].distance;
		perp_distance = rays[i].distance * cos(rays[i].ray_ang - cub3d->player.rot_ang);
		wall_strip_height = (TILE_SIZE / perp_distance) * DIST_PROJ_PLANE;
		int x = top_pixel + 1;
		while(x < WIN_HEI)
		{
			my_mlx_pixel_put(&cub3d->img, i, x, RED);
			x++;
		}
		int y = 0;
		while(y < top_pixel + 1)
		{
			my_mlx_pixel_put(&cub3d->img, i, y, BLUE);
			y++;
		}
		if(rays[i].was_vt_hit)
			rect((i * WALL_STIP_WIDTH), ((WIN_HEI / 2) - (wall_strip_height / 2)), WALL_STIP_WIDTH, wall_strip_height, cub3d, WHITE);
		else
			rect((i * WALL_STIP_WIDTH), ((WIN_HEI / 2) - (wall_strip_height / 2)), WALL_STIP_WIDTH, wall_strip_height, cub3d, GRAY);
		/*
		int texture_offset_x;
		if(rays[i].was_vt_hit)
			texture_offset_x = fmod(rays[i].wall_hit_y, 1.0) * 480;
		else
			texture_offset_x = fmod(rays[i].wall_hit_x, 1.0) * 480;
		int texture_offset_y;
		int j = 0;
		int texture_color;
		while(j < bot_pixel && j > top_pixel)
		{
			texture_offset_y = (y + (wall_strip_height / 2) - (WIN_HEI / 2) * (64 / wall_strip_height));
			/// recuperer la couleur de ma texture
			texture_color = get_texture_color(cub3d, texture_offset_x, texture_offset_y); 
			my_mlx_pixel_put(&cub3d->img, i, j++, texture_color);
		}*/
		i++;
	}
}

void	clear_color_buffer(int32_t color)
{
	for(int x = 0; x < WIN_WID; x++)
	{
		for(int y = 0; y < WIN_HEI; y++)
			color_buffer[(WIN_WID * y) + x] = color;
	}
}

void	render(t_cub3d *cub3d)
{
	t_ray *rays;

	init_img(&cub3d->img, &cub3d->win);
	update(cub3d);
	clear_color_buffer(RED);
	rays = cast_all_rays(cub3d);

	//render_3d_walls(rays, cub3d);
	render_minimap(cub3d);	
	free(rays);
	render_player(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->img.img, 0, 0);
}

int main()
{
	t_cub3d		cub3d;
	int cub3d_running;
	char		**grid;

	//INIT
	cub3d_running = init_win(&cub3d.win);
	cub3d.win.mlx_p = mlx_init();
	cub3d.win.win_p = mlx_new_window(cub3d.win.mlx_p, WIN_WID, WIN_HEI, "cub3d");
	init_img(&cub3d.img, &cub3d.win);
	init_player(&cub3d.player);
	init_map(&cub3d.map);
	//init_texture(cub3d);
	//
	
	color_buffer = (int32_t *)malloc(sizeof(int32_t) * (int32_t)(WIN_WID * WIN_HEI));

	grid =  malloc(sizeof(char*) * 11);
	grid[0] = "111111111111111";
	grid[1] = "100000000000101";
	grid[2] = "100001000000101";
	grid[3] = "111100000010101";
	grid[4] = "100000000010101";
	grid[5] = "100000001111101";
	grid[6] = "100000000000001";
	grid[7] = "100000000000001";
	grid[8] = "111111100111101";
	grid[9] = "100000000000001";
	grid[10] = "111111111111111";
	cub3d.grid = grid;

	//RENDER
	while(cub3d_running)
	{
		render(&cub3d);
		//KEY EVENTS
		mlx_hook(cub3d.win.win_p, 2, 1L<<0, key_pressed, &cub3d);
		mlx_hook(cub3d.win.win_p, 3, 1L<<1, key_released, &cub3d.player);
		mlx_loop(cub3d.win.mlx_p);
	}
}
