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

#include "../includes/cub.h"

void	render_mini_map(t_cub *cub)
{
	int		i;
	int		j;
	t_pos	pos;

	i = -1;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (++j < cub->data.cols)
		{
			pos.x = MINIMAP_SCALE * j;
			pos.y = MINIMAP_SCALE * i;
			if (cub->grid[i][j] == '1')
				square(pos, MINIMAP_SCALE, cub, GRAY);
			else
				square(pos, MINIMAP_SCALE, cub, BLACK);
		}
	}
}

void	render_mini_player(t_cub *cub)
{
	int		i;

	i = -1;
	while (++i < cub->win.wid)
		render_line(&cub->rays[i].line, cub, GREEN);
	render_line(&cub->rays[cub->win.wid / 2].line, cub, WHITE);
}

void	render_mini_sprt(t_cub *cub)
{
	int		i;
	int		j;
	t_pos	pos;

	i = -1;
	while (++i < cub->data.rows)
	{
		j = -1;
		while (++j < cub->data.cols)
		{
			pos.x = MINIMAP_SCALE * j;
			pos.y = MINIMAP_SCALE * i;
			if (cub->grid[i][j] == '2')
				my_mlx_pixel_put(&cub->win, pos.x, pos.y, BLUE);
		}
	}
}
