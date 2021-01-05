/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:03:10 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/05 18:08:42 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "parsing.h"
#include <fcntl.h>

void init_struct(t_struct *data)
{
	int i;

	i = 0;
	data->resolution[0] = -1;
	data->resolution[1] = -1;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->sp_path = NULL;
	while(i < 3)
	{
		data->floor[i] = -1;
		data->ceiling[i] = -1;
		i++;
	}
}

int parse_line(t_struct *data, char *line)
{
	if(data->no_path != NULL)
		printf("%s\n", data->no_path);
	return 0;
}

int read_file(char *cub, t_struct *data)
{
	char *line;
	int file;
	int res;

	file = open(cub, O_RDONLY);
	res = 1;
	while(res > 0)
	{
		res = get_next_line(file, &line);
		if(res != -1)
		{
			printf(res ? "%s\n" : "%s", line);
			parse_line(data, line);
			free(line);
		}
		else
			printf("error gnl\n");
	}
	return 0;
}

int main(int ac, char **av)
{
	t_struct data;
	if(ac == 1)
	{
		printf(ERROR_MSG);
		printf(ERROR_CUB);
	}
	else if(ac > 3)
	{
		printf(ERROR_MSG);
		printf(ERROR_ARG);
	}
	else
	{
		init_struct(&data);
		read_file(av[1], &data);
	}
	return 0;
}
