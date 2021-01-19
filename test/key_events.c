/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:04:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/19 13:53:00 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int keycode, t_cub3d *cub3d)
{
	if (keycode == 'z' || keycode == KEY_W)
		cub3d->player.walk_d = 1;
	else if (keycode == 's')
		cub3d->player.walk_d = -1;
	if (keycode == 'q' || keycode == KEY_A)
		cub3d->player.turn_d = -1;
	if (keycode == 'd')
		cub3d->player.turn_d = 1;
	update(cub3d);
}

int		key_released(int keycode, t_player *player)
{
	if (keycode == 'z' || keycode == KEY_W)
		player->walk_d = 0;
	else if (keycode == 's')
		player->walk_d = 0;
	if (keycode == 'q' || keycode == KEY_A)
		player->turn_d = 0;
	if (keycode == 'd')
		player->turn_d = 0;
}
