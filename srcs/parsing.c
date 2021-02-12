/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 15:50:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub_ext(char *map_file)
{
	int i;

	i = 0;
	while (map_file[i])
		i++;
	i -= 4;
	if (!strcmp(&map_file[i], ".cub"))
		return (1);
	return (is_error("Map argument is not ending with .cub"));
}

int line_data(t_cub3d *cub3d, char *line, t_list **list)
{
	char **line_data;
	int res;
	static int grid_flag;

	int i = 0;
	line_data = ft_split(line, ' ');
	if (*line_data && *line_data[0] == 'R')
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
		if (valid = 0)
			return (0);
	}
	close(fd);
	if (!grid_parsing(cub3d, list))
		return (0);
	return (1);
}

void	init_cub3d(t_cub3d *cub3d, char *file)
{
	init_win(&cub3d->win);
	init_img(&cub3d->img, &cub3d->win);
	init_grid(&cub3d->data);
	init_player(&cub3d->player);
	init_texture(cub3d);
}

int		end_cub3d(t_cub3d *cub3d)
{
	free_text(cub3d->text);
	//sprites to free;
	free_grid(cub3d);
	if(cub3d->win.img.img)
		free_img(&cub3d->win);
	free_win(&cub3d->win);
	exit(0);
}

int main(int ac, char **av)
{
	t_cub3d cub3d;

	if (ac == 3 && av[2] == "--save")
		return (0);
	//else if (ac == 3)
	else
	{
		if (cub_ext(av[1]))
		{
			init_cub3d(&cub3d, av[1]);
			if (parsing(&cub3d, av[1]))
			{
				printf("Cub3d is launching..\n");
				run_cub3d(&cub3d);
			}
			end_cub3d(&cub3d);
		}
	}
	//else
	//	return(is_error("Wrong numbers of arguments"));
	return (0);
}
