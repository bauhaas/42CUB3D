/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 00:52:53 by bahaas           ###   ########.fr       */
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

int	grep_color(t_text text, int x, int y)
{
	char *dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > text.wid)
		x = text.wid;
	if (y > text.hei)
		y = text.hei;
	dst = text.data + (y * text.line_length + x * text.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}


void	render_wall(t_cub3d *cub3d, t_ray rays, int i, float wall_hei)
{
	int				text_x;
	int				text_y;
	int				color;
	int				j;

	j = rays.top_pixel;
	if (rays.was_vt_hit)
		text_x = fmod(rays.wall_hit_y, 64);
	else
		text_x = fmod(rays.wall_hit_x, 64);
	while (j < rays.bot_pixel)
	{
		text_y = (j + (wall_hei / 2) - (cub3d->win.hei / 2)) *
		(cub3d->text[rays.id].hei / wall_hei);
		color = grep_color(cub3d->text[rays.id], text_x, text_y);
		my_mlx_pixel_put(&cub3d->win, i, j, color);
		j++;
	}
}

void render_floor(t_cub3d *cub3d, t_ray rays, int i)
{
	int j;

	j = rays.bot_pixel;
	while(j < cub3d->win.hei)
	{
		my_mlx_pixel_put(&cub3d->win, i, j, cub3d->data.floor);
		j++;
	}
}

void render_ceil(t_cub3d *cub3d, t_ray rays, int i)
{
	int j;

	j = 0;
	while(j < rays.top_pixel)
	{
		my_mlx_pixel_put(&cub3d->win, i, j, cub3d->data.ceil);
		j++;
	}
}

void				render_3d(t_ray *rays, t_cub3d *cub3d)
{
	float			wall_dist;
	float			wall_hei;
	int				top_pixel;
	int				bot_pixel;
	int				i;

	i = 0;
	while (i < cub3d->win.wid)
	{
		wall_dist = rays[i].distance * cos(rays[i].ray_ang -
			cub3d->player.rot_ang);
		wall_hei = (TILE_SIZE / wall_dist) * cub3d->data.dist_proj_plane;
		//wall_hei = cub3d->data.dist_proj_plane / wall_dist;
		top_pixel = (cub3d->win.hei / 2) - (wall_hei / 2);
		bot_pixel = (cub3d->win.hei / 2) + (wall_hei / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		if (bot_pixel > cub3d->win.hei)
			bot_pixel = cub3d->win.hei;
		rays[i].top_pixel = top_pixel;
		rays[i].bot_pixel = bot_pixel;
		render_ceil(cub3d, rays[i], i);
		render_floor(cub3d, rays[i], i);
		render_wall(cub3d, rays[i], i, wall_hei);
		i++;
	}
}

void	render(t_cub3d *cub3d)
{
	cub3d->rays = cast_all_rays(cub3d);
	render_3d(cub3d->rays, cub3d);
	render_minimap(cub3d);	
	render_player(cub3d);
	//render_sprites(cub3d);
	free(cub3d->rays);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->win.img.img, 0, 0);
}

void run_cub3d(t_cub3d *cub3d)
{
	load_win(&cub3d->win);
	load_img(&cub3d->win);
	mlx_hook(cub3d->win.win_p, 2, 1L<<0, key_pressed, cub3d);
	mlx_hook(cub3d->win.win_p, 3, 1L<<1, key_released, &cub3d->player);
	mlx_hook(cub3d->win.win_p, 33, 1L<<17, &end_cub3d, cub3d);
	render(cub3d);
	mlx_loop(cub3d->win.mlx_p);
}
