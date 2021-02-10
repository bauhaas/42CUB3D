/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:47:04 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:47:00 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		ft_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char		*dst;

	if (x >= 0 && x < win->width &&
		y >= 0 && y < win->height)
	{
		dst = win->image.addr + (y * win->image.line_length +
			x * (win->image.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void		draw_lines(t_win *win, t_point a, t_point b, int color)
{
	t_point		c;
	float		length;
	t_point		add_point;
	float		i;

	c.x = b.x - a.x;
	c.y = b.y - a.y;
	length = sqrt(c.x * c.x + c.y * c.y);
	add_point.x = c.x / length;
	add_point.y = c.y / length;
	c.x = a.x;
	c.y = a.y;
	i = 0.0;
	while (i < length)
	{
		ft_mlx_pixel_put(win, c.x, c.y, color);
		c.x += add_point.x;
		c.y += add_point.y;
		i++;
	}
}

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		cube(t_win *win, t_point a, int size, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j <= size)
	{
		i = 0;
		while (i <= size)
		{
			ft_mlx_pixel_put(win, a.x + i, a.y + j, color);
			i++;
		}
		j++;
	}
}

void		rect(t_win *win, t_point a, t_point coord, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j < coord.x)
	{
		i = 0;
		while (i < coord.y)
		{
			ft_mlx_pixel_put(win, a.x + j, a.y + i, color);
			i++;
		}
		j++;
	}
}
