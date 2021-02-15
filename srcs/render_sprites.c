/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:29:18 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 19:53:49 by bahaas           ###   ########.fr       */
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

void	sprite_display(t_cub3d *cub3d, int i)
{
	t_coord text;
	float	dist;
	int		color;
	int		background;
	int y;
	int x;

	x = -1;
	while(cub3d->sprites[i].first_x + x < 0)
		x++;
	while (++x < cub3d->sprites[i].hei && cub3d->sprites[i].first_x + x < cub3d->win.wid)
	{
		dist = cub3d->rays[(int)(cub3d->sprites[i].first_x + x)].distance;
		if (dist > cub3d->sprites[i].distance)
		{
			text.x =  x * cub3d->text[4].wid / cub3d->sprites[i].hei;
			y = cub3d->sprites[i].top_pixel - 1;
			while (++y < cub3d->sprites[i].bot_pixel)
			{
				background = grep_color(cub3d->text[4], 0, 0);
				text.y = (y + (cub3d->sprites[i].hei / 2) -
					(cub3d->win.hei / 2)) * (cub3d->text[4].hei / cub3d->sprites[i].hei);
				if (text.y < 0)
					text.y = 0;
				color = grep_color(cub3d->text[4], text.x, text.y);
				if (color != background)
					my_mlx_pixel_put(&cub3d->win, cub3d->sprites[i].first_x + x, y, color);
			}
		}
	}
}

void	fill_sprites_data(t_cub3d *cub3d)
{
	int				i;
	int				top_y;
	int				bot_y;

	i = -1;
	while (++i < cub3d->data.num_sprites)
	{
		if (cub3d->sprites[i].visibility)
		{
			cub3d->sprites[i].hei = (cub3d->data.dist_proj_plane) /
				(cos(cub3d->sprites[i].ang) * cub3d->sprites[i].distance);
			top_y = (cub3d->win.hei / 2) - (cub3d->sprites[i].hei / 2);
			bot_y = (cub3d->win.hei / 2) + (cub3d->sprites[i].hei / 2);
			if (top_y < 0)
				top_y = 0;
			if (bot_y > cub3d->win.hei)
				bot_y = cub3d->win.hei;
			cub3d->sprites[i].bot_pixel = bot_y;
			cub3d->sprites[i].top_pixel = top_y;
			cub3d->sprites[i].first_x = cub3d->data.dist_proj_plane *
				tan(cub3d->sprites[i].ang) + (cub3d->win.wid / 2) -
				(cub3d->sprites[i].hei / 2);
			sprite_display(cub3d, i);
		}
	}
}

void	sort_sprites(t_cub3d *cub3d)
{
	t_sprite tmp;
	int i;
	int j;

	i = -1;
	while(++i < cub3d->data.num_sprites)
	{
		j = i + 1;
		if(cub3d->sprites[i].distance < cub3d->sprites[j].distance)
		{
			tmp = cub3d->sprites[i];
			cub3d->sprites[i] = cub3d->sprites[j];
			cub3d->sprites[j] = tmp;
		}
	}
}

void	render_sprites(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while (++i < cub3d->data.num_sprites)
		fill_sprites(cub3d, i);
	sort_sprites(cub3d);
	fill_sprites_data(cub3d);
}
