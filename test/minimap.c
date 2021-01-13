/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/13 02:40:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_minimap_wall_square(int x, int y, int size, t_img *img)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, GRAY);
			j++;
		}
		i++;
	}
}

void	render_view_line(int x, int y, int size, t_img *img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		my_mlx_pixel_put(img, x + 4.5 + j, y + 4.5 + i, WHITE);
		i++;
	}
}

void	render_player(t_img *img, t_player *player)
{
	int x;
	int y;

	x = player->x;
	y = player->y;
	render_minimap_wall_square(x * MINI_SIZE / 2 + 10, y * MINI_SIZE / 2 + 10,
			player->radius, img);
	render_view_line(x * MINI_SIZE / 2 + 10, y * MINI_SIZE / 2 + 10, 20, img);
}
