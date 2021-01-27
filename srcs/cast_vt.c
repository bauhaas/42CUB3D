/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:45:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/27 23:54:51 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
typedef struct	s_dcast
{
	float xstep;
	float ystep;
	float xinter;
	float yinter;
	float hit_x;
	float hit_y;
	float next_x;
	float next_y;
	int found_wall;

}				t_dcast;
*/
t_dcast	fill_vt_data(t_cub3d *cub3d, t_ray *ray)
{
	t_dcast	vt_data;

	vt_data.found_wall = 0;
	vt_data.hit_x = 0;
	vt_data.hit_y = 0;
	vt_data.xinter = floor(cub3d->player.pos.x / TILE_SIZE) * TILE_SIZE;
	vt_data.xinter +=  ray->is_right ? TILE_SIZE : 0;
	vt_data.yinter = cub3d->player.pos.y + (vt_data.xinter - cub3d->player.pos.x) * tan(ray->ray_ang);
	vt_data.xstep = TILE_SIZE;
	vt_data.xstep *= ray->is_left ? -1 : 1;
	vt_data.ystep = TILE_SIZE * tan(ray->ray_ang);
	vt_data.ystep *= (ray->is_up && vt_data.ystep > 0) ? -1 : 1;
	vt_data.ystep *= (ray->is_down && vt_data.ystep < 0) ? -1 : 1;
	vt_data.next_x = vt_data.xinter;
	vt_data.next_y = vt_data.yinter;
	return (vt_data);
}

void 	vt_cast(t_ray *ray, t_cub3d *cub3d)
{
	t_dcast	vt_data;
	int i;

	i = 0;
	vt_data = fill_vt_data(cub3d, ray);
	if(ray->is_left)
		i = 1;
	//printf("pos x %f\n", cub3d->player.pos.x);
	//printf("pos y %f\n", cub3d->player.pos.y);
	while(vt_data.next_x >= 0 && vt_data.next_x <= WIN_WID && vt_data.next_y >= 0 && vt_data.next_y <= WIN_HEI)
	{
		//my_mlx_pixel_put(&cub3d->img, vt_data.next_x, vt_data.next_y, RED);
		if(grid_is_wall(vt_data.next_x - i, vt_data.next_y, cub3d))
		{
			//printf("test\n");
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