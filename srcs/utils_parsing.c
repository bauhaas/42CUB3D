/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:43:26 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/05 01:02:39 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int count_cols(t_list *list)
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

int is_num(char *num)
{
	int i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
		{
			printf("doesn't have numeric values only\n");
			return (0);
		}
	}
	return (1);
}

void	free_split(char ***split)
{
	int i;

	i = -1;
	while((*split)[++i])
		{
			free((*split)[i]);
			(*split)[i] = NULL;
		}
	free(*split);
	*split = NULL;
}
