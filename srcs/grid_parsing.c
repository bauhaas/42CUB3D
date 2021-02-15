/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:59:14 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 00:25:10 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		check_surrounding(char **grid, int x, int y)
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
			|| !grid[y - 1][x + 1])
		return (0);
	return (1);
}

int		is_grid(t_cub *cub, int cols, int y, int len)
{
	int		x;
	int		next_row;
	int		prev_row;

	x = -1;
	next_row = 0;
	if (y > 0)
		prev_row = ft_strlen(cub->grid[y - 1]);
	if (y < cub->data.rows - 1)
	{
		if (y + 1 != cub->data.cols - 1)
			next_row = ft_strlen(cub->grid[y + 1]);
	}
	while (cub->grid[y][++x])
	{
		if ((ft_strchr("02", cub->grid[y][x])) && (y == 0 || x == 0
			|| y == (cols - 1) || x == (len - 1)
			|| x - 1 > prev_row || x + 1 > next_row
			|| !check_surrounding(cub->grid, x, y)))
			return (is_error("Grid not fully closed"));
		if (!ft_strchr(" 012", cub->grid[y][x]))
			return (is_error("Invalid char in grid"));
	}
	return (1);
}

int		check_grid(t_cub *cub)
{
	int		y;
	int		len;

	y = -1;
	while (++y < cub->data.rows)
	{
		len = ft_strlen(cub->grid[y]);
		if (!is_grid(cub, cub->data.cols - 1, y, len))
			return (0);
	}
	printf("Grid OK\n");
	return (1);
}
