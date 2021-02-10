/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:40:40 by clorin            #+#    #+#             */
/*   Updated: 2021/01/13 10:44:10 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_win(t_win *win)
{
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->width = 0;
	win->height = 0;
	win->num_rays = 0;
	win->c_color = -1;
	win->f_color = -1;
	init_image(&win->image);
}

void		free_win(t_win *win)
{
	if (win->mlx_ptr)
	{
		if (win->win_ptr)
		{
			if (win->image.img)
				free_image(win);
			mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		}
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
	win->mlx_ptr = NULL;
}
