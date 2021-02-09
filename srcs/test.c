/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/09 19:26:49 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	if (!grid_is_wall(new_player_x, new_player_y, cub3d))
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
			my_mlx_pixel_put(&cub3d->win, x + j, y + i, color);
			i++;
		}
		j++;
	}
}

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
	while (i < NUM_RAYS)
	{
		top_pixel = (WIN_HEI / 2) - (wall_strip_height / 2);
		top_pixel = top_pixel < 0 ? 0 : top_pixel;
		bot_pixel = (WIN_HEI / 2) + (wall_strip_height / 2);
		bot_pixel = bot_pixel > WIN_HEI ? WIN_HEI : bot_pixel;
		ray_distance = rays[i].distance;
		perp_distance = rays[i].distance * cos(rays[i].ray_ang - cub3d->player.rot_ang);
		wall_strip_height = (TILE_SIZE / perp_distance) * DIST_PROJ_PLANE;
		//int x = WIN_HEI / 2;
		//while (x < WIN_HEI)
		int x = top_pixel;
		while (x < WIN_HEI)
		{
			my_mlx_pixel_put(&cub3d->win, i, x, RED);
			x++;
		}
		int y = 0;
		while (y < top_pixel + 1)
		//while (y < WIN_HEI / 2)
		{
			my_mlx_pixel_put(&cub3d->win, i, y, BLUE);
			y++;
		}
		if (rays[i].was_vt_hit)
			rect((i * WALL_STIP_WIDTH), ((WIN_HEI / 2) - (wall_strip_height / 2)), WALL_STIP_WIDTH, wall_strip_height, cub3d, WHITE);
		else
			rect((i * WALL_STIP_WIDTH), ((WIN_HEI / 2) - (wall_strip_height / 2)), WALL_STIP_WIDTH, wall_strip_height, cub3d, GRAY);
		/*
		int texture_offset_x;
		if (rays[i].was_vt_hit)
			texture_offset_x = fmod(rays[i].wall_hit_y, 1.0) * 480;
		else
			texture_offset_x = fmod(rays[i].wall_hit_x, 1.0) * 480;
		int texture_offset_y;
		int j = 0;
		int texture_color;
		while (j < bot_pixel && j > top_pixel)
		{
			texture_offset_y = (y + (wall_strip_height / 2) - (WIN_HEI / 2) * (64 / wall_strip_height));
			/// recuperer la couleur de ma texture
			texture_color = get_texture_color(cub3d, texture_offset_x, texture_offset_y); 
			my_mlx_pixel_put(&cub3d->img, i, j++, texture_color);
		}*/
		i++;
	}
}

void	render(t_cub3d *cub3d)
{
	t_ray *rays;

	load_img(&cub3d->win);
	update(cub3d);
	rays = cast_all_rays(cub3d);
//	printf("test\n");
//	render_minimap(cub3d);	
	render_3d_walls(rays, cub3d);
//	printf("test2\n");
	free(rays);
//	printf("test3\n");
//	render_player(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->win.img.img, 0, 0);
}

void run_cub3d(t_cub3d *cub3d)
{
	cub3d->win.mlx_p = mlx_init();
	cub3d->win.win_p = mlx_new_window(cub3d->win.mlx_p, cub3d->win.wid, cub3d->win.hei, "cub3D");
	load_img(&cub3d->win);
//	printf("player pos x : %f\n", cub3d->player.pos.x);
//	printf("player pos y : %f\n", cub3d->player.pos.y);
//	printf("win wid: %d\n", cub3d->win.wid);
//	printf("win hei : %d\n", cub3d->win.hei);
	//RENDER
		render(cub3d);
		//KEY EVENTS
		mlx_hook(cub3d->win.win_p, 2, 1L<<0, key_pressed, cub3d);
		mlx_hook(cub3d->win.win_p, 3, 1L<<1, key_released, &cub3d->player);
		mlx_hook(cub3d->win.win_p, 33, 1L<<17, &end_cub3d, cub3d);
		mlx_loop(cub3d->win.mlx_p);
}
