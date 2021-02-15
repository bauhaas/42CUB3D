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

#include "../includes/cub.h"

void	is_visible(t_cub *cub, int i)
{
	float angle;

	angle = cub->sprites[i].ang;
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;
	angle = abs(angle);
	if (angle < (FOV / 2))
		cub->sprites[i].visibility = 1;
	else
		cub->sprites[i].visibility = 0;
}

float	find_angle(t_cub *cub, int i)
{
	float			dx;
	float			dy;
	float			angle;

	dx = cub->sprites[i].coord.x - cub->player.pos.x;
	dy = cub->sprites[i].coord.y - cub->player.pos.y;
	angle = atan2(dy, dx) - cub->player.rot_ang;
	return (angle);
}
