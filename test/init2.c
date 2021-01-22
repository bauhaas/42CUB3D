/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:24:15 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/22 15:24:31 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	init_line(t_coord a, t_coord b)
{
	t_line line;

	line.start.x = a.x;
	line.start.y = a.y;
	line.end.x = b.x;
	line.end.y = b.y;
	return(line);
}

t_coord	init_coord(float x, float y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	return(coord);
}
