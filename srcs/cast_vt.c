/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:45:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 01:04:02 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_dcast	fill_vt_data(t_cub3d *cub3d, t_ray *ray)
{
	t_dcast	vt_data;

	vt_data.found_wall = 0;
	vt_data.hit_x = 0;
	vt_data.hit_y = 0;
//	vt_data.xinter = floor(cub3d->player.pos.x / TILE_SIZE) * TILE_SIZE;
	vt_data.xinter = floor(cub3d->player.pos.x);
//	vt_data.xinter +=  ray->is_right ? TILE_SIZE : 0;
	vt_data.xinter +=  ray->is_right ? 1.0 : 0;
	vt_data.yinter = cub3d->player.pos.y + (vt_data.xinter -
			cub3d->player.pos.x) * tan(ray->ray_ang);
//	vt_data.xstep = TILE_SIZE;
	vt_data.xstep = 1.0;
	vt_data.xstep *= ray->is_left ? -1 : 1;
//	vt_data.ystep = TILE_SIZE * tan(ray->ray_ang);
	vt_data.ystep = 1.0 * tan(ray->ray_ang);
	vt_data.ystep *= (ray->is_up && vt_data.ystep > 0) ? -1 : 1;
	vt_data.ystep *= (ray->is_down && vt_data.ystep < 0) ? -1 : 1;
	vt_data.next_x = vt_data.xinter;
	vt_data.next_y = vt_data.yinter;
	return (vt_data);
}

void 	vt_cast(t_ray *ray, t_cub3d *cub3d)
{
	t_dcast	vt_data;
	int		i;

	i = 0;
	vt_data = fill_vt_data(cub3d, ray);
	if (ray->is_left)
		i = 1;
	while (vt_data.next_x >= 0 && vt_data.next_x <= cub3d->win.wid &&
			vt_data.next_y >= 0 && vt_data.next_y <= cub3d->win.hei)
	{
		if (grid_is_wall(vt_data.next_x - i, vt_data.next_y, cub3d))
		{
			vt_data.hit_y = vt_data.next_y;
			vt_data.hit_x = vt_data.next_x;
			vt_data.found_wall = 1;
			break;
		}
		else
		{
			vt_data.next_x += vt_data.xstep;
			vt_data.next_y += vt_data.ystep;
		}
	}
	ray->vt_hit.x = vt_data.hit_x;
	ray->vt_hit.y = vt_data.hit_y;
	ray->found_vt_wall = vt_data.found_wall;
}
