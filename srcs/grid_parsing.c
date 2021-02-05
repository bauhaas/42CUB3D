/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:59:14 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/04 19:01:59 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_surrounding(char **grid, int x, int y)
{
	if (grid[y + 1][x] == ' '
		|| grid[y - 1][x] == ' '
		|| grid[y][x + 1] == ' '
		|| grid[y][x - 1] == ' '
		|| grid[y + 1][x - 1] == ' '
		|| grid[y + 1][x + 1] == ' '
		|| grid[y - 1][x - 1] == ' '
		|| grid[y - 1][x + 1] == ' ')
		return (0);
	if (!grid[y + 1][x - 1]
		|| !grid[y + 1][x + 1]
		|| !grid[y - 1][x - 1]
		|| !grid[y - 1][x + 1]
		)
		return (0);
	return (1);
}

int check_grid(t_cub3d *cub3d)
{
	int x;
	int y;
	int next_row;
	int prev_row;

	x = 0;
	y = 0;
/*	while (cub3d->grid[y][x])
	{
		if (check_surrounding(cub3d->grid, x, y) || )
		{
			printf("Grid not fully closed");
			return (0);
		}
		if (!ft_strchr("012NSEW", cub3d->grid[y][x]))
		{
			printf("Invalid char in grid");
			return (0);
		}
		x++;
	}*/
	printf("Grid not checked\n");
	return (1);
}
