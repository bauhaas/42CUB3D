/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 17:51:58 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Each line of the map is saved into a list element and added at the end
** to have it in the good order.
*/

int		fill_list_grid(t_cub *cub, char *line, t_list **list)
{
	t_list	*new_elem;

	cub->data.grid_flag = 1;
	new_elem = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(list, new_elem);
	return (1);
}

/*
** Help us to determine the content of the line then save the data to our
** cub3d parameter. grid_flag is here to know when we reached map parameter.
*/

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
		cub->data.res = fill_color(cub, line);
	else if (*line_data && *line_data[0] == '1')
		cub->data.res = fill_list_grid(cub, line, list);
	else if (!*line_data && cub->data.grid_flag)
		cub->data.res = is_error("empty line in or after grid parameter");
	else if (cub->data.grid_flag)
		cub->data.res = is_error("args after grid");
	free_split(&line_data, 0);
	return (cub->data.res);
}

/*
** Last malloc and data attribution before loading the game.
*/

int		last_load(t_cub *cub)
{
	init_healthbar(cub);
	cub->data.fov = 85 * (M_PI / 180);
	cub->data.dist_proj_plane = (cub->win.wid / 2) / (tan(cub->data.fov / 2));
	cub->rays = malloc(sizeof(t_ray) * cub->win.wid);
	if (!cub->rays)
		return (is_error("Malloc space rays"));
	cub->ray_load = 1;
	return (1);
}

/*
** Check if we have all the required parameters to load the game.
*/

int		check_missing(t_cub *cub)
{
	if (!cub->data.grid_flag)
		return (is_error("Map is missing"));
	if (!cub->data.ceil)
		return (is_error("Ceil color is missing"));
	if (!cub->data.floor)
		return (is_error("Floor color is missing"));
	if (!cub->win.wid)
		return (is_error("Resolution is missing"));
	if (!cub->text[0].name)
		return (is_error("North texture is missing"));
	if (!cub->text[1].name)
		return (is_error("South texture is missing"));
	if (!cub->text[2].name)
		return (is_error("West texture is missing"));
	if (!cub->text[3].name)
		return (is_error("East texture is missing"));
	if (!cub->text[4].name)
		return (is_error("Sprite texture is missing"));
	if (cub->win.wid == -1 || cub->win.hei == -1)
		return (is_error(" resolution or has a 0 value"));
	return (last_load(cub));
}

/*
** Read the .cub file and analyse it line by line.
*/

int		parsing(t_cub *cub, char *map_file, t_list **list)
{
	int		fd;
	int		valid;
	int		i;
	char	*line;

	i = 1;
	fd = open(map_file, O_RDONLY);
	if (read(fd, 0, 0) < 0)
		return (is_error("map file isn't valid"));
	if (fd < 0)
		return (is_error("map file couldn't open"));
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i != 0)
			valid = line_data(cub, line, list);
		free(line);
		if (valid == 0)
			return (0);
	}
	close(fd);
	return (1);
}
