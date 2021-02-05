/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:05:33 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/04 21:05:23 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int fill_res(t_cub3d *cub3d, char **data)
{
	int x;
	int y;

	if(cub3d->win.wid == -1 && cub3d->win.hei == -1)
	{
		if (data[1] && data[2] && is_num(data[1]) && is_num(data[2]))
		{
			x = ft_atoi(data[1]);
			y = ft_atoi(data[2]);
			if (x > 0 && y > 0)
			{
				cub3d->win.wid = x;
				cub3d->win.hei = y;
				printf("resolution OK\n");
				return (1);
			}
		}
		else
		{
			printf("resolution isn't a correct number\n");
			return (0);
		}
	}
	else
	{
		printf("resolution is declared twice\n");
		return (0);
	}
}
