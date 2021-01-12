/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/12 18:15:43 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_player(t_data *img, t_player *player)
{
	int x = player->x;
	int y = player->y;

	minimap_draw(x * MINI_SIZE/2 + 10, y * MINI_SIZE/2 + 10, player->radius, img);
	view_line_draw(x * MINI_SIZE/2 + 10, y * MINI_SIZE/2 + 10, 20, img);
}


