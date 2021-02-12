/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:15:43 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 20:26:22 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_win(t_win *win)
{
	win->mlx_p = NULL;
	win->win_p = NULL;
	win->wid = -1;
	win->hei = -1;
}

void	free_win(t_cub3d *cub3d)
{
	if (cub3d->win.mlx_p)
	{
		if (cub3d->win.win_p)
			mlx_destroy_window(cub3d->win.mlx_p, cub3d->win.win_p);
		mlx_destroy_display(cub3d->win.mlx_p);
		free(cub3d->win.mlx_p);
	}
	cub3d->win.mlx_p = NULL;
}

void	load_win(t_win *win)
{
	win->win_p = mlx_new_window(win->mlx_p, win->wid, win->hei, "cub3D");
}
