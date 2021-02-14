/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 02:08:30 by bahaas           ###   ########.fr       */
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

void	render_minimap(t_cub3d *cub3d)
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
			coord.x = MINIMAP_SCALE * (j);
			coord.y = MINIMAP_SCALE * (i);
			if (cub3d->grid[i][j] == '1')
				square(coord, MINIMAP_SCALE, cub3d, GRAY);
			else
				square(coord, MINIMAP_SCALE, cub3d, BLACK);
		}
	}
}

/*
 * DDA Line Algorithm
 */
/*
   void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
   {
   int delta_x = line->end.x - line->start.x;
   int delta_y = line->end.y - line->start.y;

   int longest_side = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);
   float x_inc = delta_x / (float)longest_side;
   float y_inc = delta_y / (float)longest_side;

   float curr_x = line->start.x;
   float curr_y = line->start.y;
   for(int i = 0; i < longest_side; i++)
   {
   my_mlx_pixel_put(&cub3d->win, round(curr_x), round(curr_y), color);
   curr_x += x_inc;
   curr_y += y_inc;
   }
   }*/

void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
{
	t_coord		c;
	float		length;
	t_coord		add_point;
	float		i;

	c.x = line->end.x - line->start.x;
	c.y = line->end.y - line->start.y;
	length = sqrt(c.x * c.x + c.y * c.y);
	add_point.x = c.x / length;
	add_point.y = c.y / length;
	c.x = line->start.x;
	c.y = line->start.y;
	i = 0.0;
	while (i < length)
	{
		my_mlx_pixel_put(&cub3d->win, c.x, c.y, color);
		c.x += add_point.x;
		c.y += add_point.y;
		i++;
	}
}

void render_player(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while(++i < cub3d->win.wid)
		render_view_line(&cub3d->rays[i].line, cub3d, GREEN);
	render_view_line(&cub3d->rays[cub3d->win.wid / 2].line, cub3d, WHITE);
}


void		rect(t_win *win, t_coord a, t_coord coord, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j < coord.x)
	{
		i = 0;
		while (i < coord.y)
		{
			my_mlx_pixel_put(win, a.x + j, a.y + i, color);
			i++;
		}
		j++;
	}
}

void	minimap_sprites(t_cub3d *cub3d, int i)
{
	t_coord start;
	t_coord end;

	start.x = (cub3d->sprites[i].coord.x) * MINIMAP_SCALE;
	start.y = (cub3d->sprites[i].coord.y) * MINIMAP_SCALE;
	end.x = 5;
	end.y = 5;
	if(cub3d->sprites[i].visibility)
		rect(&cub3d->win, start, end, RED);
	else
		rect(&cub3d->win, start, end, BLUE);
}
