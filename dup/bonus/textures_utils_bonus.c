/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:09:02 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:52:49 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int					get_tex_color(t_texture tex, int x, int y)
{
	char			*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > tex.width)
		x = tex.width;
	if (y > tex.height)
		y = tex.height;
	dst = tex.data + (y * tex.line_length + x * tex.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}

int					is_texture(char **tab_line)
{
	if (ft_strequ(*tab_line, "NO") || ft_strequ(*tab_line, "SO")
		|| ft_strequ(*tab_line, "WE") || ft_strequ(*tab_line, "EA")
		|| ft_strequ(*tab_line, "S"))
		return (TRUE);
	else
		return (FALSE);
}
