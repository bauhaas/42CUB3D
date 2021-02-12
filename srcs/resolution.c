/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:05:33 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 20:32:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_res(t_cub3d *cub3d)
{
	int x;
	int y;

	mlx_get_screen_size(cub3d->win.mlx_p, &x, &y);
	if (cub3d->win.wid > x)
		cub3d->win.wid = x;
	if (cub3d->win.hei > y)
		cub3d->win.hei = y;
}

int		fill_res(t_cub3d *cub3d, char **data)
{
	int x;
	int y;

	cub3d->win.mlx_p = mlx_init();
	if (!cub3d->win.mlx_p)
		return (is_error("Couldn't init MLX"));
	if (cub3d->win.wid == -1 && cub3d->win.hei == -1)
	{
		if (data[1] && data[2] && is_num(data[1]) && is_num(data[2]))
		{
			x = ft_atoi(data[1]);
			y = ft_atoi(data[2]);
			if (x > 0 && y > 0)
			{
				cub3d->win.wid = x;
				cub3d->win.hei = y;
				check_res(cub3d);
				printf("resolution OK\n");
				return (1);
			}
		}
		else
			return (is_error("Resolution isn't a valid number"));
	}
	return (is_error("Resolution is declared twice"));
}
