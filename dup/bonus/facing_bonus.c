/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facing_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:01:16 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:49:12 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int				is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int				is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}

int				is_ray_facing_right(float angle)
{
	return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int				is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}
