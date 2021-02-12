/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 16:34:46 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int line_data(t_cub3d *cub3d, char *line, t_list **list)
{
	char **line_data;
	int res;
	static int grid_flag;

	int i = 0;
	res = 0;
	line_data = ft_split(line, ' ');
	if(!*line_data && !grid_flag)
		res = 1;
	else if (*line_data && *line_data[0] == 'R')
		res = fill_res(cub3d, line_data);
	else if (*line_data && is_texture(line_data))
		res = fill_texture(cub3d, line_data);
	else if (*line_data && (*line_data[0] == 'F' || *line_data[0] == 'C'))
		res = fill_color(cub3d, line_data);
	else if (*line_data && *line_data[0] == '1')
	{
		grid_flag = 1;
		res = fill_list_grid(cub3d, line, list);
	}
	else if (!*line_data && grid_flag)
		res = is_error("empty line in or after grid parameter");
	else if (grid_flag)
		res = is_error("args after grid");
	free_split(&line_data);
	return (res);
}

int	parsing(t_cub3d *cub3d, char *map_file)
{
	int fd;
	int valid;
	int i;
	char *line;
	t_list *list;

	i = 1;
	list = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (is_error("map file couldn't open"));
	while (i > 0)
	{
		i  = get_next_line(fd, &line);
		if (i != 0)
			valid = line_data(cub3d, line, &list);
		free(line);
		if (valid == 0)
			return (0);
	}
	close(fd);
	if (!grid_parsing(cub3d, list))
		return (0);
	if(!load_texture(cub3d))
		return (0);
	return (1);
}
