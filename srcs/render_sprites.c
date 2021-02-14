/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:29:18 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 22:35:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_sprites(t_cub3d *cub3d, int i)
{
	cub3d->sprites[i].distance = p_dist(cub3d->player.pos.x,
			cub3d->player.pos.y, cub3d->sprites[i].coord.x,
			cub3d->sprites[i].coord.y);
	cub3d->sprites[i].ang = find_angle(cub3d, i);
	is_visible(cub3d, i);
}

void	draw_sprite(t_cub3d *cub3d, t_sprite sprite, t_coord pos,
					t_coord offset)
{
	int				color;
	int				no_color;

	no_color = grep_color(cub3d->text[4], 0, 0);
	offset.y = (pos.y + (sprite.hei / 2.0) - (cub3d->win.hei / 2.0)) *
	(cub3d->text[4].hei / sprite.hei);
	if (offset.y < 0)
		offset.y = 0;
	color = grep_color(cub3d->text[4], offset.x, offset.y);
	if (color != no_color)
		my_mlx_pixel_put(&cub3d->win, sprite.first_x + pos.x, pos.y, color);
}

void	render_sprite(t_cub3d *cub3d, t_sprite sprite)
{
	t_coord			point;
	t_coord			offset;
	float			dist_ray;

	point.x = -1;
	while (sprite.first_x + point.x < 0)
		point.x++;
	while (++point.x < sprite.hei && sprite.first_x + point.x < cub3d->win.wid)
	{
		dist_ray = cub3d->rays[(int)(sprite.first_x + point.x)].distance;
		if (dist_ray > cub3d->sprites[sprite.id].distance)
		{
			offset.x = point.x * cub3d->text[4].wid / sprite.hei;
			point.y = sprite.top_pixel - 1;
			while (++point.y < sprite.bot_pixel)
				draw_sprite(cub3d, sprite, point, offset);
		}
	}
}

void	sprite_data(t_cub3d *cub3d, t_sprite *sprite)
{
	int				i;
	int				top;
	int				bot;

	i = -1;
	while (++i < cub3d->data.num_sprites)
	{
		if (sprite[i].visibility)
		{
			sprite[i].id = i;
			sprite[i].hei = (cub3d->data.dist_proj_plane) /
			(cos(sprite[i].ang) * sprite[i].distance);
			top = (cub3d->win.hei / 2.0) - (sprite[i].hei / 2);
			if (top < 0)
				top = 0;
			bot = (cub3d->win.hei / 2.0) + (sprite[i].hei / 2);
			if (bot > cub3d->win.hei)
				bot = cub3d->win.hei;
			sprite[i].top_pixel = top;
			sprite[i].bot_pixel = bot;
			sprite[i].first_x = cub3d->data.dist_proj_plane * tan(sprite[i].ang)
			+ (cub3d->win.wid / 2) - (sprite[i].hei / 2);
			render_sprite(cub3d, sprite[i]);
		}
	}
}

void	render_sprites(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while (++i < cub3d->data.num_sprites)
		fill_sprites(cub3d, i);
	sprite_data(cub3d, cub3d->sprites);
}
