/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:23:33 by clorin            #+#    #+#             */
/*   Updated: 2021/01/31 19:17:59 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		valid_color(int color)
{
	return (color >= 0 && color <= 255);
}

static int		parse_resol(t_game *game, char **tab)
{
	int			resol_x;
	int			resol_y;

	if (tab[1] && tab[2] && is_number(tab[1]) && is_number(tab[2]))
	{
		resol_x = ft_atoi(tab[1]);
		resol_y = ft_atoi(tab[2]);
		if (resol_x > 0 && resol_y > 0)
		{
			if (game->win.width == 0 && game->win.height == 0)
			{
				game->win.width = resol_x;
				game->win.height = resol_y;
				return (valid_resol(game));
			}
			else
				return (msg_err(TWICE_RESOLUTION, ""));
		}
		else
			return (msg_err(BAD_RESOLUTION, ""));
	}
	else
		return (msg_err(FAIL_PARS_RESOL, ""));
	return (FALSE);
}

int				parse_color(char *str)
{
	char		**rgb;
	int			color_tab[3];
	int			color;
	int			i;

	i = -1;
	rgb = ft_split(str, ',');
	while (++i < 3)
	{
		if (rgb[i] && is_number(rgb[i]) && valid_color(ft_atoi(rgb[i])))
			color_tab[i] = ft_atoi(rgb[i]);
		else
		{
			free_tab(rgb);
			free(rgb);
			msg_err(INVALID_FC_LINE, "");
			return (-1);
		}
	}
	color = create_trgb(0x0, color_tab[0], color_tab[1], color_tab[2]);
	printf("color after trgb : %d\n", color);
	free_tab(rgb);
	free(rgb);
	return (color);
}

static int		record_list_map(t_game *game, t_list **list, char *line)
{
	game->in_map = TRUE;
	if (line[0] != '\0')
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(line)));
		return (TRUE);
	}
	else
		return (msg_err(EMPTY_LINE, ""));
}

int				parse_line(char *line, t_game *game, t_list **list)
{
	char		**tab_line;
	int			ret;

	ret = TRUE;
	tab_line = ft_split(line, ' ');
	if (*tab_line && *tab_line[0] == 'R' && !game->in_map)
		ret = parse_resol(game, tab_line);
	else if (*tab_line && is_texture(tab_line) && !game->in_map)
		ret = parse_texture(game, tab_line);
	else if (*tab_line && (ft_strequ(*tab_line, "F") ||
		ft_strequ(*tab_line, "C")) && !game->in_map)
		ret = setup_color(game, tab_line);
	else if (*tab_line && *tab_line[0] == '1')
		ret = record_list_map(game, list, line);
	else if (!*tab_line && game->in_map)
		ret = msg_err(EMPTY_LINE, "");
	else if (*tab_line && !game->in_map)
		ret = msg_err(BAD_ARG_CUB, line);
	else if (game->in_map)
		ret = msg_err(BAD_END_MAP, "");
	if (*tab_line)
		free_tab(tab_line);
	free(tab_line);
	return (ret);
}
