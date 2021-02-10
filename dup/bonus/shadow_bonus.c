/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:31:40 by clorin            #+#    #+#             */
/*   Updated: 2021/01/21 12:21:37 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			shadow(int c, float dist)
{
	int		color_shad;
	float	coeff;
	int		r;
	int		g;
	int		b;

	color_shad = 0;
	coeff = (1 - dist / 20);
	if (coeff > 1)
		coeff = 1;
	if (coeff < 0)
		coeff = 0;
	r = (c & 0x00FF0000) * coeff;
	g = (c & 0x0000FF00) * coeff;
	b = (c & 0x000000FF) * coeff;
	color_shad = (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
	return (color_shad);
}
