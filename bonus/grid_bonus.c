/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/03/10 11:24:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_grid(t_cub *cub)
{
	cub->data.rows = 0;
	cub->data.cols = 0;
	cub->data.ceil = 0;
	cub->data.floor = 0;
	cub->data.grid_flag = 0;
	cub->data.res = 0;
	cub->data.dist_pplane = 0.0;
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

/*
** Duplicate the content of my list in my cub structure.
*/

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

/*
** Find number of rows and cols of the map. Malloc the required space to save
** the map parameter then fill it in my cub structure.
*/

int		grid_alloc(t_cub *cub, t_list *list)
{
	int cols;
	int rows;

	cols = count_cols(list);
	rows = ft_lstsize(list);
	if (!cols || !rows)
		return (is_error("Map has 0 cols or 0 rows"));
	cub->grid = malloc(sizeof(char *) * rows + 1);
	cub->data.cols = cols;
	cub->data.rows = rows;
	if (!cub->grid)
		return (is_error("Not enough memory to malloc the map"));
	fill_grid(cub, list);
	return (1);
}

/*
** Malloc and fill my map. Then check if it's a valid map.
*/

int		grid_parsing(t_cub *cub, t_list *list)
{
	if (!grid_alloc(cub, list))
	{
		ft_lstclear(&list, &ft_free);
		return (0);
	}
	ft_lstclear(&list, &ft_free);
	if (!check_player(cub) || !check_grid(cub) || !check_sprt(cub))
		return (0);
	return (1);
}
