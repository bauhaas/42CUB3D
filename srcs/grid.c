/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 00:24:47 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_grid(t_cub *cub)
{
	cub->data.rows = 0;
	cub->data.cols = 0;
	cub->data.ceil = -1;
	cub->data.floor = -1;
	cub->data.grid_flag = 0;
	cub->data.res = 0;
	cub->data.dist_proj_plane = 0;
	cub->data.num_sprt = 0;
}

void	free_grid(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->data.rows)
	{
		free(cub->grid[i]);
		cub->grid[i] = NULL;
	}
	free(cub->grid);
}

int		fill_grid(t_cub *cub, t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		cub->grid[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	return (1);
}

int		grid_alloc(t_cub *cub, t_list *list)
{
	int cols;
	int rows;

	cols = count_cols(list);
	rows = ft_lstsize(list);
	if (!cols || !rows)
		return (is_error("grid has no cols or no rows"));
	cub->grid = malloc(sizeof(char *) * rows);
	cub->data.cols = cols;
	cub->data.rows = rows;
	if (!cub->grid)
		return (is_error("not enough memory to malloc"));
	fill_grid(cub, list);
	return (1);
}

int		grid_parsing(t_cub *cub, t_list *list)
{
	grid_alloc(cub, list);
	ft_lstclear(&list, &ft_free);
	if (!check_player(cub) || !check_grid(cub) || !check_sprt(cub))
		return (0);
	return (1);
}
