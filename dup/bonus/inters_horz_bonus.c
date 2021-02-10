/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inters_horz_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:17:30 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:51:32 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_point			inter_horiz(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			player;

	player = game->player.coord;
	intercept.y = floor(player.y);
	if (is_ray_facing_down(ray_angle))
		intercept.y += 1.0;
	intercept.x = player.x + ((intercept.y - player.y) / tan(ray_angle));
	return (intercept);
}

static t_point			step_horz(float ray_angle)
{
	t_point			step;

	step.y = 1.0;
	if (is_ray_facing_up(ray_angle))
		step.y *= -1.0;
	step.x = 1.0 / tan(ray_angle);
	if ((is_ray_facing_left(ray_angle) && step.x > 0.0) ||
		(is_ray_facing_right(ray_angle) && step.x < 0.0))
		step.x *= -1.0;
	return (step);
}

t_point					horz_wall_hit(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			step;
	t_point			next_touch;
	t_point			to_check;
	t_point			no_point;

	no_point.x = -1;
	no_point.y = -1;
	intercept = inter_horiz(ray_angle, game);
	step = step_horz(ray_angle);
	cpy_point(&next_touch, &intercept);
	while (next_touch.x >= 0.0 && next_touch.x <= game->win.width
		&& next_touch.y >= 0.0 && next_touch.y <= game->win.height)
	{
		cpy_point(&to_check, &next_touch);
		if (is_ray_facing_up(ray_angle))
			to_check.y -= 1.0;
		if (is_wall_at(game, to_check))
			return (next_touch);
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	return (no_point);
}
