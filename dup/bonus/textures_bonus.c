/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 11:22:52 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:50:51 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void				init_texture(t_game *game)
{
	int				i;

	i = 0;
	while (i < 5)
	{
		game->tex[i].tex_ptr = NULL;
		game->tex[i].data = NULL;
		game->tex[i].file = NULL;
		game->tex[i].width = 0;
		game->tex[i].height = 0;
		game->tex[i].bits_per_pixel = 0;
		game->tex[i].line_length = 0;
		game->tex[i].endian = 0;
		i++;
	}
}

static int			valid_texture(t_game *game, char *file, int nb)
{
	int				fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (file)
			return (msg_err(BAD_TEXTURE, file));
		else
			return (msg_err(TEXT_MISSING, "no file"));
	}
	close(fd);
	if (game->tex[nb].file)
		return (msg_err(TWICE_TEXTURE, ""));
	game->tex[nb].file = ft_strdup(file);
	return (TRUE);
}

int					load_textures(t_game *game)
{
	int				i;

	i = 0;
	while (i < 5)
	{
		game->tex[i].tex_ptr = mlx_xpm_file_to_image(game->win.mlx_ptr,
		game->tex[i].file, &game->tex[i].width, &game->tex[i].height);
		if (game->tex[i].tex_ptr)
		{
			game->tex[i].data = mlx_get_data_addr(game->tex[i].tex_ptr,
			&game->tex[i].bits_per_pixel,
			&game->tex[i].line_length, &game->tex[i].endian);
		}
		else
		{
			msg_err(BAD_TEXTURE, game->tex[i].file);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int					parse_texture(t_game *game, char **tab)
{
	if (ft_strequ(*tab, "NO"))
		return (valid_texture(game, tab[1], NORTH));
	else if (ft_strequ(*tab, "SO"))
		return (valid_texture(game, tab[1], SOUTH));
	else if (ft_strequ(*tab, "WE"))
		return (valid_texture(game, tab[1], WEST));
	else if (ft_strequ(*tab, "EA"))
		return (valid_texture(game, tab[1], EAST));
	else if (ft_strequ(*tab, "S"))
		return (valid_texture(game, tab[1], SPRITE));
	return (FALSE);
}

void				free_texture(t_win *win, t_texture texture[5])
{
	int				i;

	i = 0;
	while (i < 5)
	{
		if (texture[i].file)
			free(texture[i].file);
		if (win->mlx_ptr && texture[i].tex_ptr)
		{
			mlx_destroy_image(win->mlx_ptr, texture[i].tex_ptr);
			texture[i].tex_ptr = NULL;
			texture[i].data = NULL;
		}
		i++;
	}
}
