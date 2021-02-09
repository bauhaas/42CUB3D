/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:15:43 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/09 17:37:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void  init_win(t_win *win)
{
	win->mlx_p = NULL;
	win->win_p = NULL;
	win->wid = -1;
	win->hei = -1;
	win->tot_rays = 0;
}

void free_win(t_win *win)
{
	if(win->mlx_p)
	{
		if(win->win_p)
			mlx_destroy_window(win->mlx_p, win->win_p);
		mlx_destroy_display(win->mlx_p);
		free(win->mlx_p);
	}
	win->mlx_p = NULL;
}