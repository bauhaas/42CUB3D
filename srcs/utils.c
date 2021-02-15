/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 01:18:48 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 01:28:38 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	normalize(float ray_ang)
{
	ray_ang = fmod(ray_ang, (2 * M_PI));
	if (ray_ang < 0)
		ray_ang += 2 * M_PI;
	return (ray_ang);
}

int		grid_is_wall(float x, float y, t_cub3d *cub3d)
{
	int grid_x;
	int grid_y;

	if (x < 0 || x > cub3d->win.wid || y < 0 || y > cub3d->win.hei)
		return (TRUE);
	grid_x = floor(x);
	grid_y = floor(y);
	if (grid_x >= cub3d->data.cols || grid_y >= cub3d->data.rows)
		return (TRUE);
	if (cub3d->grid[grid_y][grid_x] == '1')
		return (TRUE);
	else
		return (FALSE);
}

float	p_dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		grep_color(t_text text, int x, int y)
{
	char *dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > text.wid)
		x = text.wid;
	if (y > text.hei)
		y = text.hei;
	dst = text.data + (y * text.line_length + x * text.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}
