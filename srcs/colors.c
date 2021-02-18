/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:03:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/18 15:53:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		is_rgb(char *color)
{
	int	res;

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
	if (cub->data.ceil == -1)
		cub->data.ceil = hex_color;
	else
		return (is_error("Ceil color is declared twice"));
	printf("ceiling color OK\n");
	return (1);
}

int		fill_floor(t_cub *cub, int hex_color)
{
	if (cub->data.floor == -1)
		cub->data.floor = hex_color;
	else
		return (is_error("Floor color is declared twice"));
	printf("floor color OK\n");
	return (1);
}

/*
** I consider only the following format correct : [0-255],[0-255],[0-255].
** If the content of each color is valid, I'll convert it to a single rgb value
** Then fill ceil/floor color parameter.
*/

int		fill_color(t_cub *cub, char **line)
{
	char	**color;
	int		int_color[3];
	int		rgb;
	int		i;

	color = ft_split(line[1], ',');
	i = -1;
	while (++i < 3)
	{
		if (!is_rgb(color[i]) && !is_num(color[i]))
		{
			free_split(&color);
			return (0);
		}
		int_color[i] = ft_atoi(color[i]);
	}
	rgb = rgb_value(int_color[0], int_color[1], int_color[2]);
	if (strcmp(line[0], "C") == 0)
		fill_ceil(cub, rgb);
	else
		fill_floor(cub, rgb);
	free_split(&color);
	return (1);
}
