/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:54:11 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 22:36:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_sprites(t_cub *cub, int i, int x, int y)
{
	cub->sprites[i].coord.x = x + 0.001;
	cub->sprites[i].coord.y = y + 0.001;
	cub->sprites[i].distance = -1;
	cub->sprites[i].ang = 0;
	cub->sprites[i].texture = 0;
	cub->sprites[i].visibility = 0;
}

void	free_sprite(t_cub *cub)
{
	free(cub->sprites);
	cub->sprites = NULL;
}

int		load_sprites(t_cub *cub)
{
	int i;
	int j;
	int id;

	i = -1;
	id = 0;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (++j < cub->data.cols)
		{
			if (cub->grid[i][j] == '2' && id < cub->data.num_sprites)
			{
				init_sprites(cub, id, j, i);
				id++;
			}
		}
	}
	return (1);
}

void	num_sprites(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (++j < cub->data.cols)
		{
			if (cub->grid[i][j] == '2')
				cub->data.num_sprites++;
		}
	}
}

int		check_sprites(t_cub *cub)
{
	num_sprites(cub);
	cub->sprites = malloc(sizeof(t_sprite) * cub->data.num_sprites);
	if (!cub)
		return (is_error("Fail malloc for sprites"));
	return (1);
}
