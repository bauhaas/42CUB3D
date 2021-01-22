/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:50:16 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/22 14:49:03 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	hz_cast(t_ray *ray, t_cub3d *cub3d)
{
	float xstep;
	float ystep;
	float xintercept;
	float yintercept;

	int found_hz_wall = 0;
	float hz_wall_hit_x = 0;
	float hz_wall_hit_y = 0;

	yintercept = floor(cub3d->player.pos.y / TILE_SIZE) * TILE_SIZE; //minisize = tilesize
	yintercept +=  ray->facing_down ? TILE_SIZE : 0;
	// find x coordinate of the closest horizontal grid intersec
	xintercept = cub3d->player.pos.x + (yintercept - cub3d->player.pos.y) / tan(ray->ray_ang);

	//calculate increment of xstep and ystep
	ystep = TILE_SIZE;
	ystep *= ray->facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray->ray_ang);
	xstep *= (ray->facing_left && xstep > 0) ? -1 : 1;
	xstep *= (ray->facing_right && xstep < 0) ? -1 : 1;

	float hz_next_hor_x = xintercept;
	float hz_next_hor_y = yintercept;

	if(ray->facing_up)
		hz_next_hor_y--;
	//increment xstep and ystep till a wall is find
	while(hz_next_hor_x >= 0 && hz_next_hor_x <= WIN_WID && hz_next_hor_y >= 0 && hz_next_hor_y <= WIN_HEI)
	{
		if(grid_is_wall(hz_next_hor_x, hz_next_hor_y, cub3d))
		{
			//we found wall
			hz_wall_hit_y = hz_next_hor_y;
			hz_wall_hit_x = hz_next_hor_x;
			found_hz_wall = 1;
			break;
		}
		else
		{
			hz_next_hor_x += xstep;
			hz_next_hor_y += ystep;
		}
	}
	ray->hz_hit.x = hz_wall_hit_x;
	ray->hz_hit.y = hz_wall_hit_y;
	ray->found_hz_wall = found_hz_wall;
}

void 	vt_cast(t_ray *ray, t_cub3d *cub3d)
{
	float xstep;
	float ystep;
	float xintercept;
	float yintercept;

	int found_vt_wall = 0;
	float vt_wall_hit_x = 0;
	float vt_wall_hit_y = 0;

	xintercept = floor(cub3d->player.pos.x / TILE_SIZE) * TILE_SIZE;
	xintercept +=  ray->facing_right ? TILE_SIZE : 0;
	// find x coordinate of the closest horizontal grid intersec
	yintercept = cub3d->player.pos.y + (xintercept - cub3d->player.pos.x) * tan(ray->ray_ang);

	//calculate increment of xstep and ystep
	xstep = TILE_SIZE;
	xstep *= ray->facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray->ray_ang);
	ystep *= (ray->facing_up && ystep > 0) ? -1 : 1;
	ystep *= (ray->facing_down && ystep < 0) ? -1 : 1;

	float vt_next_hor_x = xintercept;
	float vt_next_hor_y = yintercept;

	if(ray->facing_left)
		vt_next_hor_x--;
	//increment xstep and ystep till a wall is find
	while(vt_next_hor_x >= 0 && vt_next_hor_x <= WIN_WID && vt_next_hor_y >= 0 && vt_next_hor_y <= WIN_HEI)
	{
		if(grid_is_wall(vt_next_hor_x, vt_next_hor_y, cub3d))
		{
			vt_wall_hit_y = vt_next_hor_y;
			vt_wall_hit_x = vt_next_hor_x;
			found_vt_wall = 1;
			break;
		}
		else
		{
			vt_next_hor_x += xstep;
			vt_next_hor_y += ystep;
		}
	}
	ray->vt_hit.x = vt_wall_hit_x;
	ray->vt_hit.y = vt_wall_hit_y;
	ray->found_vt_wall = found_vt_wall;
}


void	cast(t_ray *ray, t_cub3d *cub3d)
{
	hz_cast(ray, cub3d);
	vt_cast(ray, cub3d);
	float hz_dist = (ray->found_hz_wall)
		? p_dist(cub3d->player.pos.x, cub3d->player.pos.y, ray->hz_hit.x, ray->hz_hit.y)
		: FLT_MAX;
	float vt_dist = (ray->found_vt_wall)
		? p_dist(cub3d->player.pos.x, cub3d->player.pos.y, ray->vt_hit.x, ray->vt_hit.y)
		: FLT_MAX;
	ray->wall_hit_x = (hz_dist < vt_dist) ? ray->hz_hit.x : ray->vt_hit.x;
	ray->wall_hit_y = (hz_dist < vt_dist) ? ray->hz_hit.y : ray->vt_hit.y;
	ray->distance = (hz_dist < vt_dist) ? hz_dist : vt_dist;
	ray->was_vt_hit = (vt_dist < hz_dist);

	t_line line;
	line.start.x = cub3d->player.pos.x;
	line.start.y = cub3d->player.pos.y;
	line.end.x = ray->wall_hit_x;
	line.end.y = ray->wall_hit_y;
	render_view_line(&line, cub3d, GREEN);
}

t_ray *cast_all_rays(t_cub3d *cub3d)
{
	t_ray	*rays;
	float	ray_ang;
	int i;

	i = 0;
	//rays = malloc(sizeof(t_ray));
	rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if(!rays)
		return 0;
	ray_ang = cub3d->player.rot_ang - (FOV / 2);
	//printf("ray_ang before : %f\n\n", ray_ang);
	while(i < 1)
	//while(i < NUM_RAYS)
	{
		rays->ray_ang = normalize(ray_ang);
		init_ray(rays, rays->ray_ang);
		cast(rays, cub3d);
		ray_ang += FOV / NUM_RAYS;
		//printf("ray ang : %f\n", ray_ang);
		i++;
	}
	return(rays);
}

