/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:43:39 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:43:40 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	nb_col(t_list *list)
{
	int					len;
	int					max_len;

	max_len = 0;
	while (list)
	{
		right_trim(list->content);
		len = ft_strlen(list->content);
		if (len > 0)
		{
			if (max_len < len)
				max_len = len;
		}
		else
		{
			return (0);
		}
		list = list->next;
	}
	return (max_len);
}

void		init_map(t_map *map)
{
	map->name = NULL;
	map->tab = NULL;
	map->num_rows = 0;
	map->num_cols = 0;
}

static int	fill_tab(t_game *game, t_list *list)
{
	int					i;

	i = 0;
	while (list)
	{
		game->map.tab[i] = ft_strnew(game->map.num_cols);
		ft_memset(game->map.tab[i], ' ', game->map.num_cols);
		if (game->map.tab[i])
			ft_memcpy(game->map.tab[i], list->content,
				ft_strlen(list->content));
		else
			return (msg_err(FAIL_MALLOC, "(*map table)"));
		list = list->next;
		i++;
	}
	return (TRUE);
}

int			map_setup(t_game *game, t_list *list)
{
	int					max_col;
	int					max_line;

	max_col = nb_col(list);
	max_line = ft_lstsize(list);
	if (max_col == 0 || max_line == 0)
		return (msg_err(BAD_FORMAT_MAP, ""));
	game->map.num_rows = max_line;
	game->map.num_cols = max_col;
	game->map.tab = (char **)malloc(sizeof(char *) * max_line);
	if (game->map.tab)
		return (fill_tab(game, list));
	else
		return (msg_err(FAIL_MALLOC, "(**map table)"));
}
