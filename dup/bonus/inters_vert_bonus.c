/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inters_vert_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:12:12 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:43:18 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_point			inter_verti(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			player;

	player = game->player.coord;
	intercept.x = floor(player.x);
	if (is_ray_facing_right(ray_angle))
		intercept.x += 1.0;
	intercept.y = player.y + (intercept.x - player.x) * tan(ray_angle);
	return (intercept);
}

static t_point			step_vert(float ray_angle)
{
	t_point			step;

	step.x = 1.0;
	if (is_ray_facing_left(ray_angle))
		step.x *= -1.0;
	step.y = tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && step.y > 0.0)
		step.y *= -1.0;
	if (is_ray_facing_down(ray_angle) && step.y < 0.0)
		step.y *= -1.0;
	return (step);
}

t_point					vert_wall_hit(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			step;
	t_point			next_touch;
	t_point			to_check;
	t_point			no_point;

	no_point.x = -1;
	no_point.y = -1;
	intercept = inter_verti(ray_angle, game);
	step = step_vert(ray_angle);
	next_touch = intercept;
	while (next_touch.x >= 0 && next_touch.x <= game->win.width
		&& next_touch.y >= 0 && next_touch.y <= game->win.height)
	{
		to_check = next_touch;
		if (is_ray_facing_left(ray_angle))
			to_check.x -= 1.0;
		if (is_wall_at(game, to_check))
			return (next_touch);
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	return (no_point);
}
