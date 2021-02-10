/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:30:17 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:47:17 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			deal_key(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_close(game);
	else if (key == KEY_RIGHT)
		game->player.turn_dir = 1;
	else if (key == KEY_LEFT)
		game->player.turn_dir = -1;
	else if (key == KEY_UP || key == KEY_A)
		game->player.walk_dir = 1;
	else if (key == KEY_DOWN || key == KEY_W)
		game->player.walk_dir = -1;
	else if (key == KEY_S)
		game->player.trans_dir = -1;
	else if (key == KEY_D)
		game->player.trans_dir = 1;
	else if (key == KEY_M)
		game->is_minimap = !game->is_minimap;
	else if (key == KEY_B)
		save_bmp(game);
	update_player(game);
	render(game);
	return (0);
}

int			release_key(int key, t_game *game)
{
	if (key == KEY_RIGHT || key == KEY_LEFT)
		game->player.turn_dir = 0;
	else if (key == KEY_UP || key == KEY_DOWN)
		game->player.walk_dir = 0;
	else if (key == KEY_S || key == KEY_D)
		game->player.trans_dir = 0;
	return (0);
}
