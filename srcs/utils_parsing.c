/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:43:26 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/18 18:59:40 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** PARse each line of the map and save the length of the longest one.
*/

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

/*
** Check if string sent has only numeric values.
*/

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

/*
** Display error message and lead to the end of the program.
*/

int		is_error(char *str)
{
	printf("Error : %s\n", str);
	return (0);
}

/*
** Free the content used during the parsing analysis of each line.
*/

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

/*
** Check if map file has the correct extension.
*/

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
