/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:59:14 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 18:41:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** We are checking all the positions around the position we currently are.
** In case where we found out that the surrounding position doesn't exist
** or is a ' ', we have an invalid map.
*/

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

/*
** If the char we check is 0 or 2 & is on border of the map or his surrounding
** positions aren't valid. Map isn't closed.
** Then we check if the char isn't something else than a valid map char.
*/

int		is_grid(t_cub *cub, int rows, int y, int len)
{
	int		x;
	int		next_row;
	int		prev_row;

	x = -1;
	if (y > 0)
		prev_row = ft_strlen(cub->grid[y - 1]);
	if (y + 1 != rows)
		next_row = ft_strlen(cub->grid[y + 1]);
	else
		next_row = 0;
	while (cub->grid[y][++x])
	{
		if ((ft_strchr("02", cub->grid[y][x]) != NULL) && (y == 0 || x == 0
			|| y == (rows - 1) || x == (len - 1)
			|| x - 1 > prev_row || x + 1 > next_row
			|| !check_surrounding(cub->grid, x, y)))
			return (is_error("Map is not fully closed"));
		if (!ft_strchr(" 012", cub->grid[y][x]))
			return (is_error("Invalid char in map"));
	}
	return (1);
}

/*
** Check the validity of each rows in the map & if there isn't empty columns.
*/

int		check_grid(t_cub *cub)
{
	int		y;
	int		len;

	y = -1;
	while (++y < cub->data.rows)
	{
		len = ft_strlen(cub->grid[y]);
		if (!is_grid(cub, cub->data.rows, y, len))
			return (0);
	}
	return (1);
}
