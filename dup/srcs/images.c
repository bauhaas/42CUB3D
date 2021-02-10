/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:41:57 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:42:01 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			get_pixel_color(t_image img, int x, int y)
{
	char			*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > img.width)
		x = img.width;
	if (y > img.height)
		y = img.height;
	dst = img.addr + (y * img.line_length + x * img.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}

void		init_image(t_image *image)
{
	image->img = NULL;
	image->addr = NULL;
	image->bits_per_pixel = 0;
	image->line_length = 0;
	image->endian = 0;
	image->width = 0;
	image->height = 0;
}

void		creat_images(t_win *win)
{
	win->image.img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	win->image.addr = mlx_get_data_addr(win->image.img,
	&win->image.bits_per_pixel, &win->image.line_length, &win->image.endian);
	win->image.width = win->width;
	win->image.height = win->height;
}

void		free_image(t_win *win)
{
	mlx_destroy_image(win->mlx_ptr, win->image.img);
	win->image.img = NULL;
	win->image.addr = NULL;
}
