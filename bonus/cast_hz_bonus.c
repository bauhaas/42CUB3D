/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_hz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:42:58 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/18 18:56:28 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Fill all data required to find if wall was hz hit.
** hit_x & hit_y = points where it hits the wall.
** yinter & xinter = coordinates of the closest hz intersection
** xstep & ystep = calculate the incrementation required
*/

t_dcast	fill_hz_data(t_cub *cub, t_ray *ray)
{
	t_dcast	hz_data;

	hz_data.found_wall = 0;
	hz_data.hit_x = 0;
	hz_data.hit_y = 0;
	hz_data.yinter = floor(cub->player.pos.y);
	hz_data.yinter += ray->is_down ? 1 : 0;
	hz_data.xinter = cub->player.pos.x + (hz_data.yinter -
			cub->player.pos.y) / tan(ray->ray_ang);
	hz_data.ystep = 1;
	hz_data.ystep *= ray->is_up ? -1 : 1;
	hz_data.xstep = 1 / tan(ray->ray_ang);
	hz_data.xstep *= (ray->is_left && hz_data.xstep > 0) ? -1 : 1;
	hz_data.xstep *= (ray->is_right && hz_data.xstep < 0) ? -1 : 1;
	hz_data.next_x = hz_data.xinter;
	hz_data.next_y = hz_data.yinter;
	return (hz_data);
}

/*
** Check if we hit a wall, if not, Increment by x and ystep and loop till
** we found a wall or reached the border of our window.
*/

void	hz_cast(t_ray *ray, t_cub *cub, int i)
{
	t_dcast	hz_data;

	hz_data = fill_hz_data(cub, ray);
	if (ray->is_up)
		i = 1;
	while (hz_data.next_x >= 0 && hz_data.next_x <= cub->win.wid &&
			hz_data.next_y >= 0 && hz_data.next_y <= cub->win.hei)
	{
		if (grid_is_wall(hz_data.next_x, hz_data.next_y - i, cub))
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
