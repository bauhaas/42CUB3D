/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:43:26 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 20:34:43 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		count_cols(t_list *list)
{
	int max;
	int i;

	max = 0;
	while (list)
	{
		i = ft_strlen(list->content);
		if (i > max)
			max = i;
		list = list->next;
	}
	return (max);
}

int		is_num(char *num)
{
	int i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (is_error("Argument sent to is_num isn't a valid number"));
	}
	return (1);
}

int		is_error(char *str)
{
	printf("Error : %s\n", str);
	return (0);
}

void	free_split(char ***split)
{
	int i;

	i = -1;
	while ((*split)[++i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}

int		cub_ext(char *map_file)
{
	int i;

	i = 0;
	while (map_file[i])
		i++;
	i -= 4;
	if (!strcmp(&map_file[i], ".cub"))
		return (1);
	return (is_error("Map argument is not ending with .cub"));
}
