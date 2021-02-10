/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:06:45 by clorin            #+#    #+#             */
/*   Updated: 2021/01/18 13:07:14 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void			draw_sprite(t_game *game, t_sprite sprite, t_point pos,
					t_point offset)
{
	int				color;
	int				no_color;

	no_color = get_tex_color(game->tex[SPRITE], 0, 0);
	offset.y = (pos.y + (sprite.height / 2.0) - (game->win.height / 2.0)) *
	(game->tex[SPRITE].height / sprite.height);
	if (offset.y < 0)
		offset.y = 0;
	color = get_tex_color(game->tex[SPRITE], offset.x, offset.y);
	if (color != no_color)
		ft_mlx_pixel_put(&game->win, sprite.first_x + pos.x, pos.y, color);
}

static void			render_sprite(t_game *game, t_sprite sprite)
{
	t_point			point;
	t_point			offset;
	float			dist_ray;

	point.x = -1;
	while (sprite.first_x + point.x < 0)
		point.x++;
	while (++point.x < sprite.height &&
		sprite.first_x + point.x < game->win.width)
	{
		dist_ray = game->tab_rays[(int)(sprite.first_x + point.x)].dist;
		if (dist_ray > game->tab_sprite[sprite.index].dist)
		{
			offset.x = point.x * game->tex[SPRITE].width / sprite.height;
			point.y = sprite.top_pixel - 1;
			while (++point.y < sprite.bot_pixel)
				draw_sprite(game, sprite, point, offset);
		}
	}
}

static void			sprite_data(t_game *game, t_sprite *sprite)
{
	int				i;
	int				top;
	int				bot;

	i = -1;
	while (++i < game->nb_sprite)
	{
		if (sprite[i].is_visible)
		{
			sprite[i].index = i;
			sprite[i].height = (game->dist_proj_plane) /
			(cos(sprite[i].angle) * sprite[i].dist);
			top = (game->win.height / 2.0) - (sprite[i].height / 2);
			if (top < 0)
				top = 0;
			bot = (game->win.height / 2.0) + (sprite[i].height / 2);
			if (bot > game->win.height)
				bot = game->win.height;
			sprite[i].top_pixel = top;
			sprite[i].bot_pixel = bot;
			sprite[i].first_x = game->dist_proj_plane * tan(sprite[i].angle)
			+ (game->win.width / 2) - (sprite[i].height / 2);
			render_sprite(game, sprite[i]);
		}
	}
}

int					scan_sprite(t_game *game)
{
	int				nb;

	nb = 0;
	while (nb < game->nb_sprite)
	{
		game->tab_sprite[nb].dist = distance(game->player.coord,
			game->tab_sprite[nb].pos);
		game->tab_sprite[nb].angle = sprite_angle(game->tab_sprite[nb].pos,
			game->player.coord, game->player.rot_angle);
		game->tab_sprite[nb].is_visible =
		sprite_visible(game->tab_sprite[nb].angle);
		nb++;
	}
	sort_sprites(game->tab_sprite, game->nb_sprite);
	sprite_data(game, game->tab_sprite);
	return (1);
}
