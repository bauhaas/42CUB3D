/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:04:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 03:11:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_pressed(int key, t_cub3d *cub3d)
{
	if (key == KEY_Z)
		cub3d->player.walk_d = 1;
	else if (key == KEY_S)
		cub3d->player.walk_d = -1;
	else if (key == KEY_LEFT)
		cub3d->player.turn_d = -1;
	else if(key == KEY_RIGHT)
		cub3d->player.turn_d = 1;
	else if(key == KEY_Q)
		cub3d->player.lateral_d = -1;
	else if(key == KEY_D)
		cub3d->player.lateral_d = 1;
	else if(key == KEY_ESC)
		end_cub3d(cub3d);
	update(cub3d, &cub3d->player);
	render(cub3d);
	return (0);
}

int		key_released(int key, t_player *player)
{
	if (key == KEY_Z || key == KEY_S)
		player->walk_d = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		player->turn_d = 0;
	else if(key == KEY_Q || key == KEY_D)
		player->lateral_d = 0;
	return (0);
}
