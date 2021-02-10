/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:37:02 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:44:25 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			fact_vect(t_point *point, float fact)
{
	point->x *= fact;
	point->y *= fact;
}

void			cpy_point(t_point *dst, t_point *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

void			add_val_point(t_point *point, float val)
{
	point->x += val;
	point->y += val;
}

float			normalize_angle(float angle)
{
	angle = fmod(angle, (2 * M_PI));
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

float			distance(t_point a, t_point b)
{
	if (a.x >= 0 && b.x >= 0)
		return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
	else
		return (FLT_MAX);
}
