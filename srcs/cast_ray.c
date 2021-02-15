/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:50:16 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 02:28:43 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	select_texture(t_ray *rays, float hz_dist, float vt_dist)
{
	rays->id = 3;
	if (rays->is_right)
		rays->id = 2;
	if (vt_dist > hz_dist)
		rays->id = 1;
	if (vt_dist > hz_dist && rays->is_up)
		rays->id = 0;
}

float	find_ray_distance(float hz_dist, float vt_dist)
{
	if (hz_dist < vt_dist)
		return (hz_dist);
	return (vt_dist);
}

float	find_ray_hit(float hz_dist, float vt_dist, float hz_hit, float vt_hit)
{
	if (hz_dist < vt_dist)
		return (hz_hit);
	return (vt_hit);
}

t_ray	cast(t_ray ray, t_cub *cub)
{
	float		hz_dist;
	float		vt_dist;
	t_coord		wall_hit;

	hz_cast(&ray, cub, 0);
	vt_cast(&ray, cub, 0);
	hz_dist = FLT_MAX;
	vt_dist = FLT_MAX;
	if (ray.found_hz_wall)
		hz_dist = p_dist(cub->player.pos.x, cub->player.pos.y,
				ray.hz_hit.x, ray.hz_hit.y);
	if (ray.found_vt_wall)
		vt_dist = p_dist(cub->player.pos.x, cub->player.pos.y,
				ray.vt_hit.x, ray.vt_hit.y);
	ray.wall_hit_x = find_ray_hit(hz_dist, vt_dist, ray.hz_hit.x, ray.vt_hit.x);
	ray.wall_hit_y = find_ray_hit(hz_dist, vt_dist, ray.hz_hit.y, ray.vt_hit.y);
	ray.distance = find_ray_distance(hz_dist, vt_dist);
	ray.was_vt_hit = (vt_dist < hz_dist);
	wall_hit = init_coord(ray.wall_hit_x, ray.wall_hit_y);
	ray.line = init_line(cub->player.pos, wall_hit);
	select_texture(&ray, hz_dist, vt_dist);
	return (ray);
}

void	cast_all_rays(t_cub *cub)
{
	float	ray_ang;
	int		i;

	i = -1;
	while (++i < cub->win.wid)
	{
		ray_ang = cub->player.rot_ang + atan((i - cub->win.wid / 2) /
				cub->data.dist_proj_plane);
		cub->rays[i].ray_ang = normalize(ray_ang);
		init_ray(&cub->rays[i], cub->rays[i].ray_ang);
		cub->rays[i] = cast(cub->rays[i], cub);
	}
}
