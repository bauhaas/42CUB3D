/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprt.c                                    :+:      :+:    :+:   */
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

	angle = cub->sprt[i].ang;
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;
	angle = abs(angle);
	if (angle < (FOV / 2))
		cub->sprt[i].visibility = 1;
	else
		cub->sprt[i].visibility = 0;
}

float	find_angle(t_cub *cub, int i)
{
	float			dx;
	float			dy;
	float			angle;

	dx = cub->sprt[i].pos.x - cub->player.pos.x;
	dy = cub->sprt[i].pos.y - cub->player.pos.y;
	angle = atan2(dy, dx) - cub->player.rot_ang;
	return (angle);
}
