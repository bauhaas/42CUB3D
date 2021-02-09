/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:19:50 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/09 19:36:00 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img(t_img *img, t_win *win)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->wid = 0;
	img->hei = 0;
}

void	load_img(t_win *win)
{
	win->img.img = mlx_new_image(win->mlx_p, win->wid, win->hei);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bits_per_pixel,
			&win->img.line_length, &win->img.endian);
	win->img.wid = win->wid;
	win->img.hei = win->hei;
}

void	free_img(t_win *win)
{
	mlx_destroy_image(win->mlx_p, win->img.img);
	win->img.img = NULL;
	win->img.addr = NULL;
}
