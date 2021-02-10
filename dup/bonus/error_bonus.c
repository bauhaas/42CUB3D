/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:50:10 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:46:37 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int					msg_err(char *msg, char *line)
{
	printf("Error\n%s", msg);
	if (*line)
	{
		printf(" (%s)\n", line);
	}
	else
		printf("\n");
	return (FALSE);
}
