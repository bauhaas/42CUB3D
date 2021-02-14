/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:50:16 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 02:03:26 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	select_texture(t_ray *rays, float hz_dist, float vt_dist)
{
	if (vt_dist > hz_dist)
	{
		if (rays->is_up)
			rays->id = 0;
		else
			rays->id = 1;
	}
	else
	{
		if (rays->is_right)
			rays->id = 2;
		else
			rays->id = 3;
	}

}
t_ray	cast(t_ray ray, t_cub3d *cub3d)
{
	float		hz_dist;
	float		vt_dist;
	t_line		line;
	t_coord		wall_hit;

	hz_cast(&ray, cub3d);
	vt_cast(&ray, cub3d);
	hz_dist = FLT_MAX;
	vt_dist = FLT_MAX;
	if (ray.found_hz_wall)
		hz_dist = p_dist(cub3d->player.pos.x, cub3d->player.pos.y,
				ray.hz_hit.x, ray.hz_hit.y);
	/*
	printf("hzdist : %f\n", hz_dist);
	printf("hzhit x : %f\n", ray.hz_hit.x);
	printf("hzhit y : %f\n", ray.hz_hit.y);
	*/
	if (ray.found_vt_wall)
		vt_dist = p_dist(cub3d->player.pos.x, cub3d->player.pos.y,
				ray.vt_hit.x, ray.vt_hit.y);
//	printf("vtdist : %f\n", vt_dist);
	ray.wall_hit_x = (hz_dist < vt_dist) ? ray.hz_hit.x : ray.vt_hit.x;
	ray.wall_hit_y = (hz_dist < vt_dist) ? ray.hz_hit.y : ray.vt_hit.y;
	ray.distance = (hz_dist < vt_dist) ? hz_dist : vt_dist;
	ray.was_vt_hit = (vt_dist < hz_dist);
	wall_hit = init_coord(ray.wall_hit_x, ray.wall_hit_y);
	ray.line = init_line(cub3d->player.pos, wall_hit);
	select_texture(&ray, hz_dist, vt_dist);
	return (ray);
}


t_ray 	*cast_all_rays(t_cub3d *cub3d)
{
	t_ray	*rays;
	float	ray_ang;
	int		i;

	i = 0;
	printf("player x : %f\n", cub3d->player.pos.x);
	printf("player y : %f\n", cub3d->player.pos.y);
	rays = malloc(sizeof(t_ray) * cub3d->win.wid);
	if (!rays)
		return 0;
	while (i < cub3d->win.wid)
	{
		ray_ang = cub3d->player.rot_ang + atan((i - cub3d->win.wid / 2) /
				cub3d->data.dist_proj_plane);
		rays[i].ray_ang = normalize(ray_ang);
		init_ray(&rays[i], rays[i].ray_ang);
		rays[i] = cast(rays[i], cub3d);
		i++;
	}
	return (rays);
}

/*
void 	cast_all_rays(t_cub3d *cub3d)
{
	float	ray_ang;
	int		i;

	i = 0;
	cub3d->rays = malloc(sizeof(t_ray) * cub3d->win.wid);
//	if (!cub3d->rays)
//		return 0;
	while (i < cub3d->win.wid)
	{
		ray_ang = cub3d->player.rot_ang + atan((i - cub3d->win.wid / 2) /
				cub3d->data.dist_proj_plane);
		cub3d->rays[i].ray_ang = normalize(ray_ang);
		init_ray(&cub3d->rays[i], cub3d->rays[i].ray_ang);
		cub3d->rays[i] = cast(cub3d->rays[i], cub3d);
		i++;
	}
}*/
