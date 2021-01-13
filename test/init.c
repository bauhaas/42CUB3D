/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 01:12:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/13 16:01:49 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->cols = 0;
	map->rows = 0;
}

void	init_player(t_player *player)
{
	player->x = 2;
	player->y = 2;
	player->radius = 9;
	player->turn_d = 0;
	player->walk_d = 0;
	player->rot_ang = M_PI / 2;
	player->rot_speed = 2 * (M_PI / 180);
	player->mov_speed = 2;
}

void	init_img(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx_p, 1000, 1000);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	init_win(t_win *win)
{
	win->mlx_p = NULL;
	win->win_p = NULL;
}
