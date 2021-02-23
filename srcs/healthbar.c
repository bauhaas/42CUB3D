/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:43:28 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/20 11:19:51 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Determine position of our healthbar. The specific numbers  multiplication
** allow us to have always the same padding regardless of the resolution used.
*/

void	init_healthbar(t_cub *cub)
{
	cub->healthbar.start.x = cub->win.wid - 0.5 * cub->win.wid;
	cub->healthbar.end.x = cub->win.wid - 0.53 * cub->win.wid;
	cub->healthbar.start.y = cub->win.hei * 0.03;
	cub->healthbar.end.y = cub->win.hei - 0.93 * cub->win.hei;
}

void	render_healthbar(t_cub *cub)
{
	rect(cub, cub->healthbar.start, cub->healthbar.end, GREEN);
}

void	render_healthbar_text(t_cub *cub)
{
	float x;
	float y;

	x = cub->healthbar.start.x + cub->healthbar.end.x / 2;
	y = cub->healthbar.end.y - cub->healthbar.start.y +
		(cub->healthbar.end.y - cub->healthbar.start.y) / 1.25;
	mlx_string_put(cub->win.mlx_p, cub->win.win_p, x, y, WHITE, "100 / 100");
}
