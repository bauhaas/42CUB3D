/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:54:11 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 16:11:49 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_sprt(t_cub *cub, int i, int x, int y)
{
	cub->sprt[i].pos.x = x + 0.5;
	cub->sprt[i].pos.y = y + 0.5;
	cub->sprt[i].dist = -1;
	cub->sprt[i].ang = 0;
	cub->sprt[i].texture = 0;
	cub->sprt[i].visibility = 0;
}

void	free_sprt(t_cub *cub)
{
	if (cub->sprt)
		free(cub->sprt);
	cub->sprt = NULL;
}

/*
** Fill sprites structure with map position of each sprites.
*/

int		load_sprt(t_cub *cub)
{
	int i;
	int j;
	int id;

	i = -1;
	id = 0;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (cub->grid[i][++j])
		{
			if (cub->grid[i][j] == '2' && id < cub->data.num_sprt)
			{
				init_sprt(cub, id, j, i);
				id++;
			}
		}
	}
	cub->sprt_load = 1;
	return (1);
}

/*
** If our current position value is 2, add 1 to total sprites.
*/

void	num_sprt(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (cub->grid[i][++j])
		{
			if (cub->grid[i][j] == '2')
				cub->data.num_sprt++;
		}
	}
}

/*
** Find the number of sprites and malloc the required space.
*/

int		check_sprt(t_cub *cub)
{
	num_sprt(cub);
	cub->sprt = malloc(sizeof(t_sprt) * cub->data.num_sprt);
	if (!cub)
		return (is_error("Fail malloc for sprt"));
	return (1);
}
