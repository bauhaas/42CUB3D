/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:07:23 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 22:22:23 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	is_visible(t_cub3d *cub3d, int i)
{
	float angle;

	angle = cub3d->sprites[i].ang;
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;
	angle = abs(angle);
	if (angle < (FOV / 2))
		cub3d->sprites[i].visibility = 1;
	else
		cub3d->sprites[i].visibility = 0;
}

float	find_angle(t_cub3d *cub3d, int i)
{
	float			dx;
	float			dy;
	float			angle;

	dx = cub3d->sprites[i].coord.x - cub3d->player.pos.x;
	dy = cub3d->sprites[i].coord.y - cub3d->player.pos.y;
	angle = atan2(dy, dx) - cub3d->player.rot_ang;
	return (angle);
}
