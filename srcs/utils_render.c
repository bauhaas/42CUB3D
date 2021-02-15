/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 22:22:51 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 18:11:05 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= win->wid && y >= 0 && y <= win->hei)
	{
		dst = win->img.addr + (y * win->img.line_length + x *
				(win->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	square(t_coord coord, int size, t_cub3d *cub3d, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i <= size)
	{
		j = -1;
		while (++j <= size)
			my_mlx_pixel_put(&cub3d->win, coord.x + j, coord.y + i, color);
	}
}

void	render_line(t_line *line, t_cub3d *cub3d, int color)
{
	t_coord		delta;
	t_coord		tmp;
	float		len;
	float		i;

	delta.x = line->end.x - line->start.x;
	delta.y = line->end.y - line->start.y;
	len = sqrt(delta.x * delta.x + delta.y * delta.y);
	tmp.x = delta.x / len;
	tmp.y = delta.y / len;
	delta.x = line->start.x;
	delta.y = line->start.y;
	i = -1;
	while (++i < len)
	{
		my_mlx_pixel_put(&cub3d->win, delta.x, delta.y, color);
		delta.x += tmp.x;
		delta.y += tmp.y;
	}
}
