/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:33:53 by clorin            #+#    #+#             */
/*   Updated: 2021/01/12 13:33:58 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		color_minimap(char wall)
{
	if (wall == '0')
		return (GRAY);
	if (wall == '1')
		return (0x00101050);
	if (wall == ' ')
		return (-1);
	else
		return (MAGENTA);
}

void			render_map(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	int				color;
	t_point			point;

	y = 0;
	while (y < game->map.num_rows)
	{
		x = 0;
		while (x < game->map.num_cols)
		{
			color = color_minimap(game->map.tab[y][x]);
			if (color != -1)
			{
				point.x = x * game->fact_minimap;
				point.y = y * game->fact_minimap;
				cube(&game->win, point,
				game->fact_minimap, color);
			}
			x++;
		}
		y++;
	}
}

void			render_player(t_game *game)
{
	t_point			a;
	t_point			b;

	cpy_point(&a, &game->player.coord);
	fact_vect(&a, game->fact_minimap);
	add_val_point(&a, -3.0);
	cube(&game->win, a, 6, RED);
	add_val_point(&a, 3.0);
	b.x = a.x + cos(game->player.rot_angle) * 10;
	b.y = a.y + sin(game->player.rot_angle) * 10;
	draw_lines(&game->win, a, b, BLACK);
}

void			render_ray_map(t_game *game, t_ray *rays)
{
	t_point			wall_point;
	t_point			player;
	t_ray			ray;
	int				i;

	i = 0;
	cpy_point(&player, &game->player.coord);
	fact_vect(&player, game->fact_minimap);
	while (i < game->win.num_rays)
	{
		ray = rays[i];
		wall_point = ray.wall_hit;
		fact_vect(&wall_point, game->fact_minimap);
		draw_lines(&game->win, player, wall_point, 0x00FFFF00);
		i++;
	}
}
