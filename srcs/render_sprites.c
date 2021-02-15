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

#include "../includes/cub.h"

void	fill_sprites(t_cub *cub, int i)
{
	cub->sprites[i].distance = p_dist(cub->player.pos.x,
			cub->player.pos.y, cub->sprites[i].coord.x,
			cub->sprites[i].coord.y);
	cub->sprites[i].ang = find_angle(cub, i);
	is_visible(cub, i);
}

void	sprite_display(t_cub *cub, int i)
{
	t_coord text;
	float	dist;
	int		color;
	int		background;
	int y;
	int x;

	x = -1;
	while(cub->sprites[i].first_x + x < 0)
		x++;
	while (++x < cub->sprites[i].hei && cub->sprites[i].first_x + x < cub->win.wid)
	{
		dist = cub->rays[(int)(cub->sprites[i].first_x + x)].distance;
		if (dist > cub->sprites[i].distance)
		{
			text.x =  x * cub->text[4].wid / cub->sprites[i].hei;
			y = cub->sprites[i].top_pixel - 1;
			while (++y < cub->sprites[i].bot_pixel)
			{
				background = grep_color(cub->text[4], 0, 0);
				text.y = (y + (cub->sprites[i].hei / 2) -
					(cub->win.hei / 2)) * (cub->text[4].hei / cub->sprites[i].hei);
				if (text.y < 0)
					text.y = 0;
				color = grep_color(cub->text[4], text.x, text.y);
				if (color != background)
					my_mlx_pixel_put(&cub->win, cub->sprites[i].first_x + x, y, color);
			}
		}
	}
}

void	fill_sprites_data(t_cub *cub)
{
	int				i;
	int				top_y;
	int				bot_y;

	i = -1;
	while (++i < cub->data.num_sprites)
	{
		if (cub->sprites[i].visibility)
		{
			cub->sprites[i].hei = (cub->data.dist_proj_plane) /
				(cos(cub->sprites[i].ang) * cub->sprites[i].distance);
			top_y = (cub->win.hei / 2) - (cub->sprites[i].hei / 2);
			bot_y = (cub->win.hei / 2) + (cub->sprites[i].hei / 2);
			if (top_y < 0)
				top_y = 0;
			if (bot_y > cub->win.hei)
				bot_y = cub->win.hei;
			cub->sprites[i].bot_pixel = bot_y;
			cub->sprites[i].top_pixel = top_y;
			cub->sprites[i].first_x = cub->data.dist_proj_plane *
				tan(cub->sprites[i].ang) + (cub->win.wid / 2) -
				(cub->sprites[i].hei / 2);
			sprite_display(cub, i);
		}
	}
}

void	sort_sprites(t_cub *cub)
{
	t_sprite tmp;
	int i;
	int j;

	i = -1;
	while(++i < cub->data.num_sprites)
	{
		j = i + 1;
		if(cub->sprites[i].distance < cub->sprites[j].distance)
		{
			tmp = cub->sprites[i];
			cub->sprites[i] = cub->sprites[j];
			cub->sprites[j] = tmp;
		}
	}
}

void	render_sprites(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->data.num_sprites)
		fill_sprites(cub, i);
	sort_sprites(cub);
	fill_sprites_data(cub);
}
