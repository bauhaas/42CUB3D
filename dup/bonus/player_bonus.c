/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:42:50 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:52:13 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void				init_player(t_player *player)
{
	player->coord.x = -1;
	player->coord.y = -1;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->trans_dir = 0;
	player->rot_angle = 0;
	player->move_speed = 0.3;
	player->rot_speed = 4 * (M_PI / 180);
}

static int			valid_pos_player(t_game *game, int x, int y, char dir)
{
	if (game->player.coord.x == -1 && game->player.coord.y == -1)
	{
		game->player.coord.x = (float)x + 0.5;
		game->player.coord.y = (float)y + 0.5;
		if (dir == 'E')
			game->player.rot_angle = 0;
		else if (dir == 'S')
			game->player.rot_angle = M_PI / 2;
		else if (dir == 'W')
			game->player.rot_angle = M_PI;
		else
			game->player.rot_angle = 1.5 * M_PI;
		return (TRUE);
	}
	else
		return (msg_err(DUPLICATE_PLAYER, ""));
}

int					check_player_pos(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	int				ret;

	y = 0;
	ret = FALSE;
	while (y < game->map.num_rows)
	{
		x = 0;
		while (x < game->map.num_cols)
		{
			if (ft_strchr("NSEW", game->map.tab[y][x]))
			{
				ret = valid_pos_player(game, x, y, game->map.tab[y][x]);
				game->map.tab[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (game->player.coord.x == -1)
		return (msg_err(NO_POSITON_PLAYER, ""));
	return (ret);
}

void				update_player(t_game *game)
{
	float			move_step;
	float			ang;
	t_point			new;

	game->player.rot_angle += game->player.turn_dir * game->player.rot_speed;
	if (game->player.trans_dir != 0)
	{
		ang = game->player.rot_angle + ((M_PI / 2) * game->player.trans_dir);
		new.x = game->player.coord.x + cos(ang) * game->player.move_speed;
		new.y = game->player.coord.y + sin(ang) * game->player.move_speed;
	}
	else
	{
		move_step = game->player.walk_dir * game->player.move_speed;
		new.x = game->player.coord.x + cos(game->player.rot_angle) * move_step;
		new.y = game->player.coord.y + sin(game->player.rot_angle) * move_step;
	}
	if (!is_wall_at(game, new) && !is_sprite_at(game, new))
		game->player.coord = new;
}
