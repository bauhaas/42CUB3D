/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:24:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/04 19:24:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void init_ray(t_ray *ray, float ray_ang)
{
	ray->ray_ang = ray_ang;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->was_vt_hit = FALSE;
	ray->is_down = ray_ang > 0 && ray_ang < M_PI;
	ray->is_up = !ray->is_down;
	ray->is_right = ray_ang < 0.5 * M_PI || ray_ang > 1.5 * M_PI;
	ray->is_left = !ray->is_right;
}

t_line	init_line(t_coord a, t_coord b)
{
	t_line line;

	line.start.x = MINIMAP_SCALE * a.x;
	line.start.y = MINIMAP_SCALE * a.y;
	line.end.x = MINIMAP_SCALE * b.x;
	line.end.y = MINIMAP_SCALE * b.y;
	//line.start.x = a.x;
	//line.start.y = a.y;
	//line.end.x = b.x;
	//line.end.y = b.y;
	return (line);
}

t_coord	init_coord(float x, float y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}