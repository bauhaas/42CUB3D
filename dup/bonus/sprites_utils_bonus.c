/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:13:28 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:48:06 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void				sort_sprites(t_sprite *sprites, int nb_sprites)
{
	t_sprite		tmp;
	int				i;
	int				j;

	i = 0;
	while (i < nb_sprites)
	{
		j = i;
		while (j < nb_sprites)
		{
			if (sprites[i].dist < sprites[j].dist)
			{
				tmp = sprites[j];
				sprites[j] = sprites[i];
				sprites[i] = tmp;
				i = 0;
			}
			j++;
		}
		i++;
	}
}

float				sprite_angle(t_point sprite_pos, t_point player_pos,
		float player_rot_angle)
{
	float			dx;
	float			dy;
	float			angle;

	dx = sprite_pos.x - player_pos.x;
	dy = sprite_pos.y - player_pos.y;
	angle = atan2(dy, dx) - player_rot_angle;
	return (angle);
}

int					sprite_visible(float angle_sprite)
{
	if (angle_sprite < -M_PI)
		angle_sprite += 2 * M_PI;
	if (angle_sprite >= M_PI)
		angle_sprite -= 2 * M_PI;
	if (angle_sprite < 0)
		angle_sprite = -angle_sprite;
	return (angle_sprite < (FOV_ANGLE / 2));
}
