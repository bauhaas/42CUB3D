/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 23:48:05 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		fill_list_grid(char *line, t_list **list)
{
	t_list	*new_elem;

	new_elem = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(list, new_elem);
	return (1);
}

int		line_data(t_cub *cub, char *line, t_list **list)
{
	char		**line_data;

	line_data = ft_split(line, ' ');
	if (!*line_data && !cub->data.grid_flag)
		cub->data.res = 1;
	else if (*line_data && *line_data[0] == 'R')
		cub->data.res = fill_res(cub, line_data);
	else if (*line_data && is_texture(line_data))
		cub->data.res = fill_texture(cub, line_data);
	else if (*line_data && (*line_data[0] == 'F' || *line_data[0] == 'C'))
		cub->data.res = fill_color(cub, line_data);
	else if (*line_data && *line_data[0] == '1')
	{
		cub->data.grid_flag = 1;
		cub->data.res = fill_list_grid(line, list);
	}
	else if (!*line_data && cub->data.grid_flag)
		cub->data.res = is_error("empty line in or after grid parameter");
	else if (cub->data.grid_flag)
		cub->data.res = is_error("args after grid");
	free_split(&line_data);
	return (cub->data.res);
}

int		parsing(t_cub *cub, char *map_file)
{
	int		fd;
	int		valid;
	int		i;
	char	*line;
	t_list	*list;

	i = 1;
	list = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (is_error("map file couldn't open"));
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i != 0)
			valid = line_data(cub, line, &list);
		free(line);
		if (valid == 0)
			return (0);
	}
	close(fd);
	if (!grid_parsing(cub, list) || !load_texture(cub) ||
			!load_sprites(cub))
		return (0);
	return (1);
}
