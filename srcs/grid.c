/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 20:57:43 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_grid(t_cub3d *cub3d)
{
	cub3d->data.rows = 0;
	cub3d->data.cols = 0;
	cub3d->data.ceil = -1;
	cub3d->data.floor = -1;
	cub3d->data.grid_flag = 0;
	cub3d->data.res = 0;
}

void	free_grid(t_cub3d *cub3d)
{
	int i;

	i = 0;
	while (i < cub3d->data.rows)
	{
		free(cub3d->grid[i]);
		cub3d->grid[i] = NULL;
		i++;
	}
	free(cub3d->grid);
}

int		fill_grid(t_cub3d *cub3d, t_list *list, int cols, int rows)
{
	int i;

	i = 0;
	while (list)
	{
		cub3d->grid[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	return (1);
}

int		grid_alloc(t_cub3d *cub3d, t_list *list)
{
	int cols;
	int rows;

	cols = count_cols(list);
	rows = ft_lstsize(list);
	if (!cols || !rows)
		return (is_error("grid has no cols or no rows"));
	cub3d->grid = malloc(sizeof(char *) * rows);
	cub3d->data.cols = cols;
	cub3d->data.rows = rows;
	if (!cub3d->grid)
		return (is_error("not enough memory to malloc"));
	fill_grid(cub3d, list, cols, rows);
	return (1);
}

int		grid_parsing(t_cub3d *cub3d, t_list *list)
{
	grid_alloc(cub3d, list);
	ft_lstclear(&list, &ft_free);
	if (!check_player(cub3d) || !check_grid(cub3d))
		return (0);
	return (1);
}
