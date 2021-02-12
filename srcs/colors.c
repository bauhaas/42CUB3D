/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:03:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 20:59:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_rgb(char *color)
{
	int	res;

	res = ft_atoi(color);
	if (res >= 0 && res <= 255)
		return (1);
	return (is_error("Invalid RGB color"));
}

int		rgb_to_hex(int r, int g, int b)
{
	return (0x0 | r << 16 | g << 8 | b);
}

int		fill_ceil(t_cub3d *cub3d, int hex_color)
{
	if (cub3d->data.ceil == -1)
		cub3d->data.ceil = hex_color;
	else
		return (is_error("Ceil color is declared twice"));
	printf("ceiling color OK\n");
	return (1);
}

int		fill_floor(t_cub3d *cub3d, int hex_color)
{
	if (cub3d->data.floor == -1)
		cub3d->data.floor = hex_color;
	else
		return (is_error("Floor color is declared twice"));
	printf("floor color OK\n");
	return (1);
}

int		fill_color(t_cub3d *cub3d, char **line)
{
	char	**color;
	int		int_color[3];
	int		hex_color;
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
	hex_color = rgb_to_hex(int_color[0], int_color[1], int_color[2]);
	if (strcmp(line[0], "C") == 0)
		fill_ceil(cub3d, hex_color);
	else
		fill_floor(cub3d, hex_color);
	free_split(&color);
	return (1);
}
