/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:08 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/27 23:57:25 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub_ext(char *map_file)
{
	int i;
	
	i = 0;
	while(map_file[i])
		i++;
	if(ft_substr(map_file, i - 4, 4) != ".cub")
		return (FALSE);
	return (TRUE);
}

int	check_args(t_cub3d *cub3d, char *map_file)
{
	if(cub_ext(map_file))
		return (TRUE);
	return (FALSE);
}

int	parsing(t_cub3d *cub3d, char *map_file)
{
	int fd;
	char *line;

	fd = open(map_file, O_RDONLY);
	if(fd < 0)
		return (FALSE);
	close(fd);
	if(check_args(cub3d, map_file));
		return (TRUE);
	return (FALSE);
}
