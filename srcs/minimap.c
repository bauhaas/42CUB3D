/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 22:25:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_mini_map(t_cub3d *cub3d)
{
	int		i;
	int		j;
	t_coord	coord;

	i = -1;
	while (++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			coord.x = MINIMAP_SCALE * j;
			coord.y = MINIMAP_SCALE * i;
			if (cub3d->grid[i][j] == '1')
				square(coord, MINIMAP_SCALE, cub3d, GRAY);
			else
				square(coord, MINIMAP_SCALE, cub3d, BLACK);
		}
	}
}

void	render_mini_player(t_cub3d *cub3d)
{
	int		i;

	i = -1;
	while (++i < cub3d->win.wid)
		render_line(&cub3d->rays[i].line, cub3d, GREEN);
	render_line(&cub3d->rays[cub3d->win.wid / 2].line, cub3d, WHITE);
}

void	render_mini_sprites(t_cub3d *cub3d)
{
	int		i;
	int		j;
	t_coord	coord;

	i = -1;
	while (++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			coord.x = MINIMAP_SCALE * j;
			coord.y = MINIMAP_SCALE * i;
			if (cub3d->grid[i][j] == '2')
				my_mlx_pixel_put(&cub3d->win, coord.x, coord.y, BLUE);
		}
	}
}
