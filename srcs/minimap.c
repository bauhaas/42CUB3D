/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 20:47:11 by bahaas           ###   ########.fr       */
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
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			my_mlx_pixel_put(&cub3d->win, coord.x + j, coord.y + i, color);
	}
}

void	render_mini_map(t_cub3d *cub3d)
{
	int i;
	int j;
	t_coord coord;

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

void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
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
	i = -1.0;
	while (++i < len)
	{
		my_mlx_pixel_put(&cub3d->win, delta.x, delta.y, color);
		delta.x += tmp.x;
		delta.y += tmp.y;
	}
}

void render_mini_player(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while(++i < cub3d->win.wid)
		render_view_line(&cub3d->rays[i].line, cub3d, GREEN);
	render_view_line(&cub3d->rays[cub3d->win.wid / 2].line, cub3d, WHITE);
}

void	render_mini_sprites(t_cub3d *cub3d)
{
	int i;
	int j;
	t_coord coord;

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
