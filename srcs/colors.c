/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:03:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 21:09:57 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Looking at the first string split of our line and check if it matches C/F
*/

int		check_char(char *line)
{
	char **line_data;

	line_data = ft_split(line, ' ');
	if (*line_data[0] == 'C')
	{
		if (!ft_strcmp(line_data[0], "C"))
			return (free_split(&line_data, 1));
	}
	else if (*line_data[0] == 'F')
	{
		if (!ft_strcmp(line_data[0], "F"))
			return (free_split(&line_data, 1));
	}
	return (free_split(&line_data, 0));
}

/*
** Check if our RGB parameters has 2 ','
*/

int		check_format(char *line, int total, char **colors, t_cub *cub)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == ',')
			count++;
	}
	if (!check_char(line))
		return (0);
	if (count == total)
		return (1);
	if (!ft_strcmp(colors[0], "C"))
		cub->data.ceil = -1;
	else if (!ft_strcmp(colors[0], "F"))
		cub->data.floor = -1;
	return (is_error("One of the RGB has bad format"));
}

/*
** Check if our splitted line has 4 params : C/F R G B
*/

int		check_params(char **colors)
{
	int i;

	i = 0;
	while (colors[i])
		i++;
	if (i != 4)
		return (is_error("One of the RGB has less/more params than expected"));
	return (1);
}

int		fill_rgb(t_cub *cub, char **colors, char *line)
{
	int		i;
	int		rgb;
	int		int_color[3];

	i = 0;
	while (++i < 4)
	{
		if (!is_rgb(colors[i]) || !is_num(colors[i]))
			return (0);
		int_color[i - 1] = ft_atoi(colors[i]);
	}
	rgb = rgb_value(int_color[0], int_color[1], int_color[2]);
	if (line[0] == 'C')
	{
		if (!fill_ceil(cub, rgb))
			return (0);
	}
	else
	{
		if (!fill_floor(cub, rgb))
			return (0);
	}
	return (1);
}

int		fill_color(t_cub *cub, char *line)
{
	char	**colors;

	colors = ft_split_charset(line, " ,");
	if (check_format(line, 2, colors, cub))
	{
		if (!colors)
			return (is_error("Malloc fail for RGB colors"));
		if (!check_params(colors))
			return (free_split(&colors, 0));
		if (!fill_rgb(cub, colors, line))
			return (free_split(&colors, 0));
		return (free_split(&colors, 1));
	}
	return (free_split(&colors, 1));
}
