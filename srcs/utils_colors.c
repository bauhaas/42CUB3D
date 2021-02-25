/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:41:05 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 19:05:03 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		is_rgb(char *color)
{
	int	res;

	if (!is_num(color))
		return (is_error("One of the R/G/B value is non-numeric"));
	res = ft_atoi(color);
	if (res >= 0 && res <= 255)
		return (1);
	return (is_error("Invalid RGB color"));
}

/*
** Since each byte contains 2^8 values, and rgb values range from 0 to 255,
** we can perfeclty fit a integer (as an int is 4 bytes).
** In order to set the values programatically we use bitshifting.
*/

int		rgb_value(int r, int g, int b)
{
	return (0x0 | r << 16 | g << 8 | b);
}

int		fill_ceil(t_cub *cub, int hex_color)
{
	if (cub->data.ceil == 0)
		cub->data.ceil = hex_color;
	else
		return (is_error("Ceil color is declared twice"));
	return (1);
}

int		fill_floor(t_cub *cub, int hex_color)
{
	if (cub->data.floor == 0)
		cub->data.floor = hex_color;
	else
		return (is_error("Floor color is declared twice"));
	return (1);
}
