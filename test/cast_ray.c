/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:50:16 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/22 17:08:24 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(t_ray *ray, t_cub3d *cub3d)
{
	float		hz_dist;
	float		vt_dist;
	t_line		line;
	t_coord		wall_hit;

	hz_cast(ray, cub3d);
	vt_cast(ray, cub3d);
	hz_dist = FLT_MAX;
	vt_dist = FLT_MAX;
	if(ray->found_hz_wall)
		hz_dist = p_dist(cub3d->player.pos.x, cub3d->player.pos.y,
				ray->hz_hit.x, ray->hz_hit.y);
	if(ray->found_vt_wall)
		vt_dist = p_dist(cub3d->player.pos.x, cub3d->player.pos.y,
				ray->vt_hit.x, ray->vt_hit.y);
	ray->wall_hit_x = (hz_dist < vt_dist) ? ray->hz_hit.x : ray->vt_hit.x;
	ray->wall_hit_y = (hz_dist < vt_dist) ? ray->hz_hit.y : ray->vt_hit.y;
	ray->distance = (hz_dist < vt_dist) ? hz_dist : vt_dist;
	//ray->was_vt_hit = (vt_dist < hz_dist);
	wall_hit = init_coord(ray->wall_hit_x, ray->wall_hit_y);
	line = init_line(cub3d->player.pos, wall_hit);
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
	
	//printf("FOV: %f\n", FOV);
	//printf("NUM_RAYS: %f\n", NUM_RAYS);
	int num = NUM_RAYS;
	//printf("ray incr: %f\n", (FOV / num));
	//printf("ray incr: %f\n", (FOV / NUM_RAYS));
	//while(i < 1)
	while(i < NUM_RAYS)
	{
		rays->ray_ang = normalize(ray_ang);
		init_ray(rays, rays->ray_ang);
		cast(rays, cub3d);
		ray_ang = ray_ang + (FOV / num);
		//ray_ang = ray_ang + (FOV / NUM_RAYS);
		i++;
	}
	return(rays);
}

