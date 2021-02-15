/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 18:16:50 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_floor(t_cub3d *cub3d, t_ray rays, int i)
{
	int j;

	j = rays.bot_pixel;
	while (j < cub3d->win.hei)
	{
		my_mlx_pixel_put(&cub3d->win, i, j, cub3d->data.floor);
		j++;
	}
}

void	render_ceil(t_cub3d *cub3d, t_ray rays, int i)
{
	int j;

	j = -1;
	while (++j < rays.top_pixel)
		my_mlx_pixel_put(&cub3d->win, i, j, cub3d->data.ceil);
}

void	render_wall(t_cub3d *cub3d, int i, float wall_hei)
{
	int				text_x;
	int				text_y;
	int				color;
	int				j;

	if (cub3d->rays[i].was_vt_hit)
		text_x = fmod(cub3d->rays[i].wall_hit_y, 1) *
			cub3d->text[cub3d->rays[i].id].wid;
	else
		text_x = fmod(cub3d->rays[i].wall_hit_x, 1) *
			cub3d->text[cub3d->rays[i].id].wid;
	j = cub3d->rays[i].top_pixel - 1;
	while (++j < cub3d->rays[i].bot_pixel)
	{
		text_y = (j + (wall_hei / 2) - (cub3d->win.hei / 2)) *
			(cub3d->text[cub3d->rays[i].id].hei / wall_hei);
		color = grep_color(cub3d->text[cub3d->rays[i].id], text_x, text_y);
		my_mlx_pixel_put(&cub3d->win, i, j, color);
	}
}

void	render_3d(t_cub3d *cub3d)
{
	float			wall_dist;
	float			wall_hei;
	int				top_pixel;
	int				bot_pixel;
	int				i;

	i = -1;
	while (++i < cub3d->win.wid)
	{
		wall_dist = cub3d->rays[i].distance * cos(cub3d->rays[i].ray_ang -
			cub3d->player.rot_ang);
		wall_hei = cub3d->data.dist_proj_plane / wall_dist;
		top_pixel = (cub3d->win.hei / 2) - (wall_hei / 2);
		bot_pixel = (cub3d->win.hei / 2) + (wall_hei / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		if (bot_pixel > cub3d->win.hei)
			bot_pixel = cub3d->win.hei;
		cub3d->rays[i].top_pixel = top_pixel;
		cub3d->rays[i].bot_pixel = bot_pixel;
		render_ceil(cub3d, cub3d->rays[i], i);
		render_floor(cub3d, cub3d->rays[i], i);
		render_wall(cub3d, i, wall_hei);
	}
}

int	render(t_cub3d *cub3d)
{
	cast_all_rays(cub3d);
	//render_3d(cub3d->rays, cub3d);
	render_3d(cub3d);
	render_sprites(cub3d);
//	render_mini_map(cub3d);
//	render_mini_player(cub3d);
//	render_mini_sprites(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p,
			cub3d->win.img.img, 0, 0);
	return (1);
}
