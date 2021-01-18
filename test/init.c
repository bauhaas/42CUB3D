/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 01:12:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/15 17:47:05 by bahaas           ###   ########.fr       */
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
	player->pos.x = 0;
	player->pos.y = 0;
	player->radius = 10;
	player->turn_d = 0;
	player->walk_d = 0;
	player->rot_ang = M_PI / 2;
	player->rot_speed = 3 * (M_PI / 180);
	player->mov_speed = 10;
}

void	init_img(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx_p, WIN_WID, WIN_HEI);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	init_win(t_win *win)
{
	win->mlx_p = NULL;
	win->win_p = NULL;
}

void init_ray(t_ray *ray)
{
	ray->ray_ang = 0;
}
