/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:03:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/23 16:30:53 by bahaas           ###   ########.fr       */
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
		if (!strcmp(line_data[0], "C"))
			return (free_split(&line_data, 1));
	}
	else if (*line_data[0] == 'F')
	{
		if (!strcmp(line_data[0], "F"))
			return (free_split(&line_data, 1));
	}
	return (free_split(&line_data, 0));
}

/*
** Check if our RGB parameters has 2 ','
*/

int		check_format(char *line, int total)
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
	return (is_error("Color line has bad format"));
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
	{
		printf("wrong numbers of parameters in colors\n");
		return (free_split(&colors, 0));
	}
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
		fill_ceil(cub, rgb);
	else
		fill_floor(cub, rgb);
	return (1);
}

int		fill_color(t_cub *cub, char *line)
{
	char	**colors;

	if (check_format(line, 2))
	{
		colors = ft_split_charset(line, " ,");
		if (!colors)
			return (is_error("Malloc fail for RGB colors"));
		if (!check_params(colors))
			return (free_split(&colors, 0));
		if (!fill_rgb(cub, colors, line))
			return (free_split(&colors, 0));
		return (free_split(&colors, 1));
	}
	return (1);
}
