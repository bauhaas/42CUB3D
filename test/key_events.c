/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:04:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/12 18:09:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int keycode, t_player *player)
{
	if(keycode == 'w')
	{
		player->walk_d = 1;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->walk_d);
	}
	else if(keycode == 's')
	{
		player->walk_d = -1;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->walk_d);
	}
	if(keycode == 'a')
	{
		player->turn_d = -1;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->turn_d);
	}
	if(keycode == 'd')
	{
		player->turn_d = 1;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->turn_d);
	}
}

int		key_released(int keycode, t_player *player)
{
	if(keycode == 'w')
	{
		player->walk_d = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->walk_d);
	}
	else if(keycode == 's')
	{
		player->walk_d = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->walk_d);
	}
	if(keycode == 'a')
	{
		player->turn_d = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->turn_d);
	}
	if(keycode == 'd')
	{
		player->turn_d = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_d : %d\n", player->turn_d);
	}
}
