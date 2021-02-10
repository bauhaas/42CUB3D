/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:16:51 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:52:29 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int				valid_resol(t_game *game)
{
	int			resol_x;
	int			resol_y;

	game->win.mlx_ptr = mlx_init();
	if (!game->win.mlx_ptr)
		return (msg_err(FAIL_MLX, ""));
	if (!game->save)
	{
		mlx_get_screen_size(game->win.mlx_ptr, &resol_x, &resol_y);
		if (game->win.width > resol_x)
			game->win.width = resol_x;
		if (game->win.height > resol_y)
			game->win.height = resol_y;
	}
	game->win.num_rays = game->win.width;
	game->dist_proj_plane = (game->win.width / 2) / tan(FOV_ANGLE / 2);
	game->tab_rays = (t_ray *)malloc(sizeof(t_ray) * game->win.width);
	game->fact_minimap = floor(game->win.width * 8 / 800);
	if (game->fact_minimap > 8)
		game->fact_minimap = 8;
	if (!game->tab_rays)
		return (msg_err(FAIL_MALLOC, "tab_rays[]"));
	return (TRUE);
}

int				setup_color(t_game *game, char **tab)
{
	int			color;

	if (tab[1] && tab[1][0] != '\0')
	{
		color = parse_color(tab[1]);
		if (color == -1)
			return (FALSE);
	}
	else
		return (msg_err(BAD_COLOR, "Couldn't parse color"));
	if (ft_strequ(tab[0], "F"))
		game->win.f_color = color;
	else
		game->win.c_color = color;
	return (TRUE);
}
