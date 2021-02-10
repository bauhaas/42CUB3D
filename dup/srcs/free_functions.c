/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:11:57 by clorin            #+#    #+#             */
/*   Updated: 2021/01/14 10:12:27 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void					free_list(void *data)
{
	free(data);
	data = NULL;
}

void					free_tab(char **tab)
{
	if (tab)
	{
		while (*tab)
		{
			free(*tab);
			tab++;
		}
		tab = NULL;
	}
}

void					free_map(t_map *map)
{
	unsigned int		i;

	i = 0;
	while (i < map->num_rows)
	{
		free(map->tab[i]);
		i++;
	}
	free(map->tab);
	free(map->name);
	map->tab = NULL;
	map->name = NULL;
}
