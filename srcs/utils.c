/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 01:18:48 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 17:25:18 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Keep any angle in [0-180].
*/

float	normalize(float ray_ang)
{
	ray_ang = fmod(ray_ang, (2 * M_PI));
	if (ray_ang < 0)
		ray_ang += 2 * M_PI;
	return (ray_ang);
}

/*
** Check if [y,x] position is a wall or not.
*/

int		grid_is_wall(float x, float y, t_cub *cub)
{
	int grid_x;
	int grid_y;

	if (x < 0 || x > cub->win.wid || y < 0 || y > cub->win.hei)
		return (1);
	grid_x = floor(x);
	grid_y = floor(y);
	if (grid_x >= cub->data.cols || grid_y >= cub->data.rows)
		return (1);
	if (cub->grid[grid_y][grid_x] == '1')
		return (1);
	else
		return (0);
}

/*
** Determine the distance between 2 points.
*/

float	p_dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/*
** Return the pixel color located on the [y,x] position of our texture.
*/

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
