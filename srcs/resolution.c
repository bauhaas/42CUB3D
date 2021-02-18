/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:05:33 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/18 17:14:23 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** If given resolution is bigger than your screen size, set it to your screen
** size.
*/

void	check_res(t_cub *cub)
{
	int x;
	int y;

	mlx_get_screen_size(cub->win.mlx_p, &x, &y);
	if (cub->win.wid > x)
		cub->win.wid = x;
	if (cub->win.hei > y)
		cub->win.hei = y;
}

/*
** Check if resolution isn't decalred twice and determine if it's a valid
** resolution.
*/

int		fill_res(t_cub *cub, char **data)
{
	int x;
	int y;

	cub->win.mlx_p = mlx_init();
	if (!cub->win.mlx_p)
		return (is_error("Couldn't init MLX"));
	if (cub->win.wid == -1 && cub->win.hei == -1)
	{
		if (data[1] && data[2] && is_num(data[1]) && is_num(data[2]))
		{
			x = ft_atoi(data[1]);
			y = ft_atoi(data[2]);
			if (x > 0 && y > 0)
			{
				cub->win.wid = x;
				cub->win.hei = y;
				check_res(cub);
				printf("resolution OK\n");
				return (1);
			}
		}
		else
			return (is_error("Resolution isn't a valid number"));
	}
	return (is_error("Resolution is declared twice"));
}
