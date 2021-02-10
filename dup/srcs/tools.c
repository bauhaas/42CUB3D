/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:00:07 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 15:00:08 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void			right_trim(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
	{
		i--;
	}
	str[i + 1] = '\0';
}
