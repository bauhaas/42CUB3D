/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:13:53 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 21:58:47 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->radius = 6;
	player->turn_d = 0;
	player->walk_d = 0;
	player->rot_ang = 0;
	player->mov_speed = 0.3;
	player->rot_speed = 3 * (M_PI / 180);
}

void	update(t_cub3d *cub3d)
{
	float mov_step;
	float new_player_x;
	float new_player_y;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	cub3d->player.rot_ang = normalize(cub3d->player.rot_ang);
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	new_player_x = cub3d->player.pos.x + cos(cub3d->player.rot_ang) * mov_step;
	new_player_y = cub3d->player.pos.y + sin(cub3d->player.rot_ang) * mov_step;
	if (!grid_is_wall(new_player_x, new_player_y, cub3d))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
}

void	pos_player(t_player *player, int x, int y, char orientation)
{
	if (player->pos.x == -1 && player->pos.y == -1)
	{
		player->pos.x = x + 0.001;
		player->pos.y = y + 0.001;
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

int		check_player(t_cub3d *cub3d)
{
	int x;
	int y;
	int num_position;

	y = -1;
	num_position = 0;
	while (++y < cub3d->data.rows)
	{
		x = -1;
		while (cub3d->grid[y][++x])
		{
			if (ft_strchr("NSEW", cub3d->grid[y][x]))
			{
				pos_player(&cub3d->player, x, y, cub3d->grid[y][x]);
				num_position++;
				cub3d->grid[y][x] = '0';
				if (num_position > 1)
					return (is_error("Multiple player position in map"));
			}
		}
	}
	if (num_position == 0)
		return (is_error("No player position in map"));
	printf("player OK\n");
	return (1);
}
