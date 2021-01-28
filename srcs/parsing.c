/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/28 03:53:18 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub_ext(char *map_file)
{
	int i;

	i = 0;
	while(map_file[i])
		i++;
	i -= 4;
	if(!strcmp(&map_file[i], ".cub"))
		return (1);
	printf("Map argument is not ending by .cub\n");
	return (0);
}

int	check_args(t_cub3d *cub3d, char *map_file)
{
	printf("check args...\n");
	//	if(cub_ext(map_file) && check_resolution())
	return (1);
	/*
	   if(check_textures())
	   if(check_f_c())
	   if(check_map());
	   */
	return (1);
	return (0);
}

int isnum(char *num)
{
	int i;

	i = 0;
	printf("num : %s\n", num);
	while(num[i])
	{
		if(num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int fill_res(t_cub3d *cub3d, char **data)
{
	int x;
	int y;

	if(data[1] && data[2] && isnum(data[1]) && isnum(data[2]))
	{
		x = ft_atoi(data[1]);
		y = ft_atoi(data[2]);
		if(x > 0 && y > 0)
		{
			cub3d->win.wid = x;
			cub3d->win.hei = y;
			printf("resolution OK\n");
			return (1);
		}
	}
	else
	{
		printf("res not correct number\n");
		return (0);
	}
}

int is_rgb(char *color)
{
	int ret;

	ret = ft_atoi(color);
	printf("color : %d\n", ret);
	if(ret >= 0 && ret <= 255)
		return(1);
	return (0);
}

int	fill_floor(t_cub3d *cub3d, char **line)
{
	char **color;

	printf("line 1 : %s\n", line[1]);
	color =  ft_split(line[1], ',');
	int i = 0;
	while(color[i])
	{
		is_rgb(color[i]);
			//return(0);
		i++;
	}
	return (1);
}

int line_data(t_cub3d *cub3d, char *line)
{
	char **line_data;
	int res;

	int i = 0;
	line_data = ft_split(line, ' ');
	printf("line : %s\n", line);

	while(line_data[i] && *line_data)
	{
		printf("i : %d content : %s\n", i, line_data[i]);
		i++;
	}
	if(*line_data && *line_data[0] == 'R')
		res = fill_res(cub3d, line_data);
	else if(*line_data && *line_data == "NO")
		return (1);
	else if(*line_data && *line_data == "SO")
		return (1);
	else if(*line_data && *line_data == "WE")
		return (1);
	else if(*line_data && *line_data == "EA")
		return (1);
	else if(*line_data && *line_data[0] == 'S')
		return (1);
	else if(*line_data && *line_data[0] == 'F')
		res = fill_floor(cub3d, line_data);
	else if(*line_data && *line_data[0] == 'C')
		return (1);
	else if(*line_data && *line_data[0] == '1')
		return (1);
	else
		return (0);
	return(res);
}

int	parsing(t_cub3d *cub3d, char *map_file)
{
	int fd;
	int valid;
	int i;
	char *line;

	printf("parsing...\n");
	i = 1;
	fd = open(map_file, O_RDONLY);
	if(fd < 0)
	{
		printf("fd < 0\n");
		return (0);
	}
	while(i != 0)
	{
		i  = get_next_line(fd, &line);
		printf("gnl value : %d ", i);
		valid = line_data(cub3d, line);
		free(line);
		if(valid = 0)
			return (0);
	}
	close(fd);
	return (1);
}

int main(int ac, char **av)
{
	t_cub3d cub3d;

	if(ac == 3 && av[2] == "--save")
		return (0);
	else if(ac == 2)
	{
		printf("2 args received\n");
		if(parsing(&cub3d, av[1]))
			printf("Cub3d is launching..\n");
	}
	return (0);
}
