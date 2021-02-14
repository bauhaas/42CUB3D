/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_hz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:42:58 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 22:39:50 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_dcast	fill_hz_data(t_cub3d *cub3d, t_ray *ray)
{
	t_dcast	hz_data;

	hz_data.found_wall = 0;
	hz_data.hit_x = 0;
	hz_data.hit_y = 0;
	hz_data.yinter = floor(cub3d->player.pos.y);
	hz_data.yinter += ray->is_down ? 1.0 : 0;
	hz_data.xinter = cub3d->player.pos.x + (hz_data.yinter -
			cub3d->player.pos.y) / tan(ray->ray_ang);
	hz_data.ystep = 1.0;
	hz_data.ystep *= ray->is_up ? -1 : 1;
	hz_data.xstep = 1.0 / tan(ray->ray_ang);
	hz_data.xstep *= (ray->is_left && hz_data.xstep > 0) ? -1 : 1;
	hz_data.xstep *= (ray->is_right && hz_data.xstep < 0) ? -1 : 1;
	hz_data.next_x = hz_data.xinter;
	hz_data.next_y = hz_data.yinter;
	return (hz_data);
}

void	hz_cast(t_ray *ray, t_cub3d *cub3d, int i)
{
	t_dcast	hz_data;

	hz_data = fill_hz_data(cub3d, ray);
	if (ray->is_up)
		i = 1;
	while (hz_data.next_x >= 0 && hz_data.next_x <= cub3d->win.wid &&
			hz_data.next_y >= 0 && hz_data.next_y <= cub3d->win.hei)
	{
		if (grid_is_wall(hz_data.next_x, hz_data.next_y - i, cub3d))
		{
			hz_data.hit_y = hz_data.next_y;
			hz_data.hit_x = hz_data.next_x;
			hz_data.found_wall = 1;
			break ;
		}
		else
		{
			hz_data.next_x += hz_data.xstep;
			hz_data.next_y += hz_data.ystep;
		}
	}
	ray->hz_hit.x = hz_data.hit_x;
	ray->hz_hit.y = hz_data.hit_y;
	ray->found_hz_wall = hz_data.found_wall;
}
