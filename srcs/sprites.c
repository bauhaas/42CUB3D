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

#include "../includes/cub3d.h"

void	init_sprites(t_cub3d *cub3d, int i, int x, int y)
{
	cub3d->sprites[i].coord.x = x + 0.001;
	cub3d->sprites[i].coord.y = y + 0.001;
	cub3d->sprites[i].distance = -1;
	cub3d->sprites[i].ang = 0;
	cub3d->sprites[i].texture = 0;
	cub3d->sprites[i].visibility = 0;
}

void	free_sprite(t_cub3d *cub3d)
{
	free(cub3d->sprites);
	cub3d->sprites = NULL;
}

int		load_sprites(t_cub3d *cub3d)
{
	int i;
	int j;
	int id;

	i = -1;
	id = 0;
	while (++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			if (cub3d->grid[i][j] == '2' && id < cub3d->data.num_sprites)
			{
				init_sprites(cub3d, id, j, i);
				id++;
			}
		}
	}
	return (1);
}

void	num_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			if (cub3d->grid[i][j] == '2')
				cub3d->data.num_sprites++;
		}
	}
}

int		check_sprites(t_cub3d *cub3d)
{
	num_sprites(cub3d);
	cub3d->sprites = malloc(sizeof(t_sprite) * cub3d->data.num_sprites);
	if (!cub3d)
		return (is_error("Fail malloc for sprites"));
	return (1);
}
