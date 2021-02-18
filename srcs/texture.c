/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:21:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/18 18:59:25 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_texture(t_cub *cub)
{
	int i;

	i = 0;
	while (i < 5)
	{
		cub->text[i].ptr = NULL;
		cub->text[i].data = NULL;
		cub->text[i].name = NULL;
		cub->text[i].bits_per_pixel = 0;
		cub->text[i].line_length = 0;
		cub->text[i].endian = 0;
		cub->text[i].wid = 0;
		cub->text[i].hei = 0;
		i++;
	}
}

void	free_texture(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		if (cub->text[i].name)
		{
			free(cub->text[i].name);
			cub->text[i].name = NULL;
		}
		if (cub->text[i].ptr)
		{
			mlx_destroy_image(cub->win.mlx_p, cub->text[i].ptr);
			cub->text[i].ptr = NULL;
			cub->text[i].data = NULL;
		}
	}
}

int		load_texture(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		cub->text[i].ptr = mlx_xpm_file_to_image(cub->win.mlx_p,
				cub->text[i].name, &cub->text[i].wid, &cub->text[i].hei);
		if (!cub->text[i].ptr)
			return (is_error("bad texture content"));
		cub->text[i].data = mlx_get_data_addr(cub->text[i].ptr,
			&cub->text[i].bits_per_pixel, &cub->text[i].line_length,
			&cub->text[i].endian);
	}
	return (1);
}

/*
** Determine if the line will contain the path of a valid texture and
** try to open file related to it.
*/

int		is_texture(char **line_data)
{
	int fd;

	if (!strcmp(line_data[0], "SO")
			|| !strcmp(line_data[0], "EA")
			|| !strcmp(line_data[0], "NO")
			|| !strcmp(line_data[0], "S")
			|| !strcmp(line_data[0], "WE"))
	{
		fd = open(line_data[1], O_RDONLY);
		if (fd < 0)
			return (is_error("Texture load problem"));
		close(fd);
		return (1);
	}
	return (0);
}

/*
** Check if texture isn't already declared and fill it the name with the path
** given.
*/

int		fill_texture(t_cub *cub, char **line_data)
{
	int i;

	if (!strcmp(line_data[0], "NO"))
		i = 0;
	else if (!strcmp(line_data[0], "SO"))
		i = 1;
	else if (!strcmp(line_data[0], "WE"))
		i = 2;
	else if (!strcmp(line_data[0], "EA"))
		i = 3;
	else if (!strcmp(line_data[0], "S"))
		i = 4;
	if (cub->text[i].name)
		return (is_error("A texture is declared twice"));
	cub->text[i].name = ft_strdup(line_data[1]);
	printf("Texture %s OK\n", line_data[0]);
	return (1);
}
