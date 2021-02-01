/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/01 22:37:50 by bahaas           ###   ########.fr       */
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

int isnum(char *num)
{
	int i;

	i = 0;
	while(num[i])
	{
		if(num[i] >= '0' && num[i] <= '9')
			i++;
		else
		{
			printf("doesn't have numeric values only\n");
			return (0);
		}
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

int isrgb(char *color)
{
	int res;

	res = ft_atoi(color);
	if(res >= 0 && res <= 255)
		return(1);
	printf("invalid rgb color\n");
	return (0);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (0x0 | r << 16 | g << 8 | b);
}

int	fill_color(t_cub3d *cub3d, char **line)
{
	char **color;
	int	int_color[3];
	int hex_color;

	color =  ft_split(line[1], ',');
	int i = 0;
	while(i < 3)
	{
		if(!isrgb(color[i]) && !isnum(color[i]))
			return(0);
		int_color[i] = ft_atoi(color[i]);
		i++;
	}
	hex_color = rgb_to_hex(int_color[0], int_color[1], int_color[2]);
	if(strcmp(line[0], "C") == 0)
	{
		printf("ceiling color OK\n");
		cub3d->data.ceil = hex_color;
	}
	else
	{
		printf("floor color OK\n");
		cub3d->data.floor = hex_color;
	}
	return (1);
}

int is_texture(char **line_data)
{
	int fd;

	if(strcmp(line_data[0], "SO") == 0
			|| strcmp(line_data[0], "EA") == 0
			|| strcmp(line_data[0], "NO") == 0
			|| strcmp(line_data[0], "S") == 0
			|| strcmp(line_data[0], "WE") == 0)
	{
		fd = open(line_data[1], O_RDONLY);
		if(fd < 0)
		{
			printf("texture load problem\n");
			return (0);
		}
		close(fd);
		return(1);
	}
	return (0);
}

int	fill_texture(t_cub3d *cub3d, char **line_data)
{
	int i;

	i = 0;
	while(i < 5)
	{
		i++;
	}
	printf("test fill_texture\n");
	return (1);
}


int	fill_list_map(t_cub3d *cub3d, char *line, t_list **list)
{
	t_list *tmp;

	tmp = ft_lstnew(ft_strdup(line));
	//printf("tmp : %s\n", (char *)tmp->content);
	ft_lstadd_back(list, tmp);
	return (1);
}

int line_data(t_cub3d *cub3d, char *line, t_list **list)
{
	char **line_data;
	int res;
	static int map_flag;

	int i = 0;
	line_data = ft_split(line, ' ');
	if(*line_data && *line_data[0] == 'R')
		res = fill_res(cub3d, line_data);
	else if(*line_data && is_texture(line_data))
		res = fill_texture(cub3d, line_data);
	else if(*line_data && (*line_data[0] == 'F' || *line_data[0] == 'C'))
		res = fill_color(cub3d, line_data);
	else if(*line_data && *line_data[0] == '1')
	{
		map_flag = 1;
		res = fill_list_map(cub3d, line, list);
	}
	else
		return (0);
	return(res);
}

void ft_free(void *content_to_free)
{
	free(content_to_free);
	content_to_free = NULL;
}

int count_cols(t_list *list)
{
	int max;
	int i;

	max = 0;
	while(list)
	{	
		i = ft_strlen(list->content);
		if(i > max)
			max = i;
		list = list->next;
	}
	return(max);
}

int fill_map(t_cub3d *cub3d, t_list *list, int cols, int rows)
{
	int i;

	i = 0;
	while(list)
	{
		cub3d->grid[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	return (1);
}

void print_map(t_cub3d *cub3d, int rows)
{
	int i;
	int j;

	i = 0;
	while(i < rows)
	{
		int j = 0;
		while(cub3d->grid[i][j])
		{
			printf("%c", cub3d->grid[i][j]);
			j++;
		}
		//printf("%s\n", cub3d->grid[i]);
		printf("\n");
		i++;
	}
}

int map_alloc(t_cub3d *cub3d, t_list *list)
{
	int cols;
	int rows;

	cols = count_cols(list);
	rows = ft_lstsize(list);
	printf("rows tot : %d\n", rows);
	printf("cols tot : %d\n", cols);
	if(!cols || !rows)
	{
		printf("map has no cols or no rows\n");
		return (0);
	}
	cub3d->grid = malloc(sizeof(char *) * rows);
	cub3d->data.cols = cols;
	cub3d->data.rows = rows;
	if(!cub3d->grid)
	{
		printf("not enough memory for malloc\n");
		return (0);
	}
	fill_map(cub3d, list, cols, rows);
	print_map(cub3d, rows);
	return (1);

}

void map_parsing(t_cub3d *cub3d, t_list *list)
{
	t_list *tmp;
	tmp = list;
	while(tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	map_alloc(cub3d, list);
	ft_lstclear(&list, &ft_free);

	/*
	   int i;
	   int j;

	   i = 0;
	   printf("test\n");
	   printf("%c", *cub3d->grid[0]);
	//	if(cub3d->grid);
	while(cub3d->grid[i][j])
	{
	j = 0;
	while(cub3d->grid[i][j])
	{
	printf("%c", cub3d->grid[i][j]);
	j++;
	}
	printf("\n");
	i++;
	}
	*/
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
	if(fd < 0)
	{
		printf("map file couldn't open\n");
		return (0);
	}
	while(i != 0)
	{
		i  = get_next_line(fd, &line);
		valid = line_data(cub3d, line, &list);
		free(line);
		if(valid = 0)
			return (0);
	}
	close(fd);
	map_parsing(cub3d, list);
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
		{
			printf("Cub3d is launching..\n");
			init_game(&cub3d);
		}
	}
	return (0);
}
