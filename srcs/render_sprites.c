/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:29:18 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 20:04:47 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	fill_sprt(t_cub *cub, int i)
{
	cub->sprt[i].dist = p_dist(cub->player.pos.x,
			cub->player.pos.y, cub->sprt[i].pos.x,
			cub->sprt[i].pos.y);
	cub->sprt[i].ang = find_angle(cub, i);
	is_visible(cub, i);
}

void	sprt_display(t_cub *cub, int i)
{
	t_pos text;
	t_pos pos;
	float	dist;
	int		color;
	int		background;

	pos.x = -1;
	while(cub->sprt[i].first_x + pos.x < 0)
		pos.x++;
	while (++pos.x < cub->sprt[i].hei && cub->sprt[i].first_x + pos.x < cub->win.wid)
	{
		dist = cub->rays[(int)(cub->sprt[i].first_x + pos.x)].dist;
		if (dist > cub->sprt[i].dist)
		{
			text.x =  pos.x * cub->text[4].wid / cub->sprt[i].hei;
			pos.y = cub->sprt[i].top_px - 1;
			while (++pos.y < cub->sprt[i].bot_px)
			{
				background = grep_color(cub->text[4], 0, 0);
				text.y = (pos.y + (cub->sprt[i].hei / 2) -
					(cub->win.hei / 2)) * (cub->text[4].hei / cub->sprt[i].hei);
				if (text.y < 0)
					text.y = 0;
				color = grep_color(cub->text[4], text.x, text.y);
				if (color != background)
					my_mlx_pixel_put(&cub->win, cub->sprt[i].first_x + pos.x, pos.y, color);
			}
		}
	}
}

void	fill_sprt_data(t_cub *cub)
{
	int				i;
	int				top_y;
	int				bot_y;

	i = -1;
	while (++i < cub->data.num_sprt)
	{
		if (cub->sprt[i].visibility)
		{
			cub->sprt[i].hei = (cub->data.dist_proj_plane) /
				(cos(cub->sprt[i].ang) * cub->sprt[i].dist);
			top_y = (cub->win.hei / 2) - (cub->sprt[i].hei / 2);
			bot_y = (cub->win.hei / 2) + (cub->sprt[i].hei / 2);
			if (top_y < 0)
				top_y = 0;
			if (bot_y > cub->win.hei)
				bot_y = cub->win.hei;
			cub->sprt[i].bot_px = bot_y;
			cub->sprt[i].top_px = top_y;
			cub->sprt[i].first_x = cub->data.dist_proj_plane *
			tan(cub->sprt[i].ang) + (cub->win.wid / 2) -
			(cub->sprt[i].hei / 2);
			sprt_display(cub, i);
		}
	}
}

void	sort_sprt(t_cub *cub)
{
	t_sprt	tmp;
	int			i;
	int			j;

	i = -1;
	while(++i < cub->data.num_sprt)
	{
		j = i + 1;
		if (cub->sprt[i].dist < cub->sprt[j].dist)
		{
			tmp = cub->sprt[i];
			cub->sprt[i] = cub->sprt[j];
			cub->sprt[j] = tmp;
		}
	}
}

void	render_sprt(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->data.num_sprt)
		fill_sprt(cub, i);
	sort_sprt(cub);
	fill_sprt_data(cub);
}
