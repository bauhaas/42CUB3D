/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:21:44 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 16:45:59 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_texture(t_cub3d *cub3d)
{
	int i;

	i = 0;
	while (i < 5)
	{
		cub3d->text[i].ptr = NULL;
		cub3d->text[i].data = NULL;
		cub3d->text[i].name = NULL;
		cub3d->text[i].bits_per_pixel = 0;
		cub3d->text[i].line_length = 0;
		cub3d->text[i].endian = 0;
		cub3d->text[i].wid = 0;
		cub3d->text[i].hei = 0;
		i++;
	}
}

void	free_text(t_text *text)
{
	int i;

	i = 0;
	while (i < 5)
	{
		free(text[i].name);
		text[i].name = NULL;
		i++;
	}
}

int is_texture(char **line_data)
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

int	fill_texture(t_cub3d *cub3d, char **line_data)
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
	else if (!strcmp(line_data[0],"S"))
		i = 4;
	if (cub3d->text[i].name)
		return (is_error("A texture is declared twice"));
	cub3d->text[i].name = ft_strdup(line_data[1]);
	printf("Texture %s OK\n", line_data[0]);
	return (1);
}

int	load_texture(t_cub3d *cub3d)
{
	int i;

	i = 0;
	while(i < 5)
	{
		cub3d->text[i].ptr = mlx_xpm_file_to_image(cub3d->win.mlx_p, cub3d->text[i].name, &cub3d->text[i].wid, &cub3d->text[i].hei);
		if(!cub3d->text[i].ptr)
			return(is_error("bad texture content"));
		cub3d->text[i].data = mlx_get_data_addr(cub3d->text[i].ptr, &cub3d->text[i].bits_per_pixel, &cub3d->text[i].line_length, &cub3d->text[i].endian);
		i++;
	}
	return (1);
}
