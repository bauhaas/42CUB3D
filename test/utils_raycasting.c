/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 01:18:48 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/22 14:49:16 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize(float ray_ang)
{
	ray_ang = fmod(ray_ang, (2 * M_PI));
	if (ray_ang < 0)
	{
		ray_ang += 2 * M_PI;
	}
	return (ray_ang);
}

int		grid_is_wall(float x, float y, t_cub3d *cub3d)
{
	int grid_x;
	int grid_y;

	if (x < 0 || x > WIN_WID || y < 0 || y > WIN_HEI)
		return (TRUE);
	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_x >= MAP_COLS || grid_y >= MAP_ROWS)
		return (TRUE);
	return (cub3d->grid[grid_y][grid_x] != '0');
}

float	p_dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}