/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/16 16:59:27 by bahaas           ###   ########.fr       */
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

void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
{
	t_line	tmp;
	int		err[2];

	tmp.start.x = abs(line->end.x - line->start.x);
	tmp.start.y = abs(line->end.y - line->start.y);
	tmp.end.x = line->start.x < line->end.x ? 1 : -1;
	tmp.end.y = line->start.y < line->end.y ? 1 : -1;
	err[0] = (tmp.start.x > tmp.start.y ? tmp.start.x : -tmp.start.y) / 2;
	while (1)
	{
		my_mlx_pixel_put(&cub3d->img, line->start.x + cub3d->player.radius / 2, line->start.y + cub3d->player.radius / 2, color);
		if (line->start.x == line->end.x && line->start.y == line->end.y)
			return ;
		err[1] = err[0];
		if (err[1] > -tmp.start.x)
		{
			err[0] -= tmp.start.y;
			line->start.x += tmp.end.x;
		}
		if (err[1] < tmp.start.y)
		{
			err[0] += tmp.start.x;
			line->start.y += tmp.end.y;
		}
	}
}

void	render_player(t_cub3d *cub3d)
{
	t_line line;

	line.start.x = 0;
	line.start.y = 0;
	line.start.x += cub3d->player.pos.x;
	line.start.y += cub3d->player.pos.y;
	line.end.y = line.start.y + sin(cub3d->player.rot_ang) * 60;
	line.end.x = line.start.x + cos(cub3d->player.rot_ang) * 60;

	render_minimap_square(line.start.x, line.start.y, cub3d->player.radius, cub3d);
	render_view_line(&line, cub3d, WHITE);
}

void	render_ray(t_cub3d *cub3d, t_ray rays)
{
	t_line line;

	line.start.x = 0;
	line.start.y = 0;
	line.start.x += cub3d->player.pos.x;
	line.start.y += cub3d->player.pos.y;
	line.end.y = line.start.y + sin(rays.ray_ang) * 200;
	line.end.x = line.start.x + cos(rays.ray_ang) * 200;
	render_view_line(&line, cub3d, BLUE);
	return ;
}
