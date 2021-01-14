/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/14 16:47:22 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if( x >= 0 && x <= WIN_WID  && y >= 0 && y <= WIN_HEI)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	render_minimap_square(int x, int y, int size, t_cub3d *cub3d)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&cub3d->img, x + j, y + i, GRAY);
			j++;
		}
		i++;
	}
}

void	render_view_line(int x, int y, t_cub3d *cub3d)
{
	t_coord	last;
	t_line	line;
	int		err[2];

	last.y = y + sin(cub3d->player.rot_ang) * 20;
	last.x = x + cos(cub3d->player.rot_ang) * 20;
	line.first.x = abs(last.x - x);
	line.first.y = abs(last.y - y);
	line.last.x = x < last.x ? 1 : -1;
	line.last.y = y < last.y ? 1 : -1;
	err[0] = (line.first.x > line.first.y ? line.first.x : -line.first.y) / 2;
	while (1)
	{
		my_mlx_pixel_put(&cub3d->img, x + 4.5, y + 4.5, WHITE);
		if (x == last.x && y == last.y)
			return ;
		err[1] = err[0];
		if (err[1] > -line.first.x)
		{
			err[0] -= line.first.y;
			x += line.last.x;
		}
		if (err[1] < line.first.y)
		{
			err[0] += line.first.x;
			y += line.last.y;
		}
	}
}

void	render_player(t_cub3d *cub3d)
{
	t_coord init_pos;
	t_coord last_line_pos;

	last_line_pos.y = cub3d->player.y + sin(cub3d->player.rot_ang) * 20;
	last_line_pos.x = cub3d->player.x + cos(cub3d->player.rot_ang) * 20;
	init_pos.x += cub3d->player.x;
	init_pos.y += cub3d->player.y;

	// TO DO: CHANGE PARAMS TO ADAPAT WITH T_COORD
	render_minimap_square(init_pos.x, init_pos.y,
			cub3d->player.radius, cub3d);
	render_view_line(init_pos.x, init_pos.y, cub3d);
}


void	render_init_player(t_cub3d *cub3d)
{
	t_coord init_pos;
	t_coord last_line_pos;

	last_line_pos.y = cub3d->player.y + sin(cub3d->player.rot_ang) * 20;
	last_line_pos.x = cub3d->player.x + cos(cub3d->player.rot_ang) * 20;
	init_pos.x = cub3d->player.x;
	init_pos.y = cub3d->player.y;

	// TO DO: CHANGE PARAMS TO ADAPAT WITH T_COORD
	render_minimap_square(init_pos.x * MINI_SIZE / 2 + 20, init_pos.y * MINI_SIZE / 2 + 20,
			cub3d->player.radius, cub3d);
	render_view_line(init_pos.x * MINI_SIZE / 2 + 20, init_pos.y * MINI_SIZE / 2 + 20, cub3d);

}
