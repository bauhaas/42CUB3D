/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:13:53 by bahaas            #+#    #+#             */
/*   Updated: 2021/03/10 12:14:39 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->turn_d = 0;
	player->walk_d = 0;
	player->lateral_d = 0;
	player->rot_ang = 0;
	player->mov_speed = 0.3;
	player->rot_speed = 2 * (M_PI / 180);
}

/*
** After each movement. Determine the new position of our player.
** Knowing our player rotation angle and lenght of his step. We can find x & y
** with cos and sin.
*/

void	update(t_cub *cub, t_player *player)
{
	float mov_step;
	float lateral_ang;
	float new_x;
	float new_y;

	player->rot_ang += player->turn_d * player->rot_speed;
	player->rot_ang = normalize(player->rot_ang);
	mov_step = player->walk_d * player->mov_speed;
	new_x = player->pos.x + cos(player->rot_ang) * mov_step;
	new_y = player->pos.y + sin(player->rot_ang) * mov_step;
	if (player->lateral_d != 0)
	{
		lateral_ang = player->rot_ang + ((M_PI / 2) * player->lateral_d);
		new_x = player->pos.x + cos(lateral_ang) * player->mov_speed;
		new_y = player->pos.y + sin(lateral_ang) * player->mov_speed;
	}
	if (!grid_is_wall(new_x, new_y, cub))
	{
		cub->player.pos.x = new_x;
		cub->player.pos.y = new_y;
	}
}

/*
** Save player pos & orientation in our structure
*/

void	pos_player(t_player *player, int x, int y, char orientation)
{
	if (player->pos.x == -1 && player->pos.y == -1)
	{
		player->pos.x = x + 0.55;
		player->pos.y = y + 0.55;
		if (orientation == 'N')
			player->rot_ang = 1.5 * M_PI;
		else if (orientation == 'S')
			player->rot_ang = M_PI / 2;
		else if (orientation == 'E')
			player->rot_ang = 0;
		else if (orientation == 'W')
			player->rot_ang = M_PI;
	}
}

/*
** After filling the map. We are looking at if there is only one player pos
** & find his orientation.
*/

int		check_player(t_cub *cub)
{
	int x;
	int y;
	int num_position;

	y = -1;
	num_position = 0;
	while (++y < cub->data.rows)
	{
		x = -1;
		while (cub->grid[y][++x])
		{
			if (ft_strchr("NSEW", cub->grid[y][x]))
			{
				pos_player(&cub->player, x, y, cub->grid[y][x]);
				num_position++;
				cub->grid[y][x] = '0';
				if (num_position > 1)
					return (is_error("Multiple player position in map"));
			}
		}
	}
	if (num_position == 0)
		return (is_error("No player position in map"));
	return (1);
}
