/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:24:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 17:25:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_ray(t_ray *ray, float ray_ang)
{
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->dist = 0;
	ray->was_vt_hit = 0;
	ray->is_down = ray_ang > 0 && ray_ang < M_PI;
	ray->is_up = !ray->is_down;
	ray->is_right = ray_ang < 0.5 * M_PI || ray_ang > 1.5 * M_PI;
	ray->is_left = !ray->is_right;
}

t_line	init_line(t_pos a, t_pos b)
{
	t_line line;

	line.start.x = MINIMAP_SCALE * a.x;
	line.start.y = MINIMAP_SCALE * a.y;
	line.end.x = MINIMAP_SCALE * b.x;
	line.end.y = MINIMAP_SCALE * b.y;
	return (line);
}

t_pos	init_pos(float x, float y)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}
