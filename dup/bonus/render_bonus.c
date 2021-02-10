/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:00:47 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:50:31 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void			show_sky(t_game *game, int x, int i)
{
	float			dist_shad;

	dist_shad = (30.0 * i) / game->win.height;
	ft_mlx_pixel_put(&game->win, x, i, shadow(game->win.c_color, dist_shad));
}

static void			show_floor(t_game *game, int x, int i)
{
	float			dist_shad;

	dist_shad = (30.0 * (game->win.height - i)) / game->win.height;
	ft_mlx_pixel_put(&game->win, x, i, shadow(game->win.f_color, dist_shad));
}

static void			show_line(t_game *game, int x, t_ray ray, float wall_height)
{
	int				i;
	int				off_x;
	int				off_y;
	int				color;

	i = 0;
	while (i < ray.top_pixel)
		show_sky(game, x, i++);
	if (ray.hit_vert)
		off_x = (int)(fmod(ray.wall_hit.y, 1.0) * game->tex[ray.id].width);
	else
		off_x = (int)(fmod(ray.wall_hit.x, 1.0) * game->tex[ray.id].width);
	while (i < ray.bot_pixel)
	{
		off_y = (i + (wall_height / 2.0) - (game->win.height / 2.0)) *
		(game->tex[ray.id].height / wall_height);
		color = shadow(get_tex_color(game->tex[ray.id], off_x, off_y),
			ray.dist);
		ft_mlx_pixel_put(&game->win, x, i++, color);
	}
	while (i < game->win.height)
		show_floor(game, x, i++);
}

void				gen_3d(t_game *game, t_ray *tab_rays)
{
	int				i;
	float			perp_dist;
	float			wall_height;
	int				top_pixel;
	int				bot_pixel;

	i = 0;
	while (i < game->win.num_rays)
	{
		perp_dist = tab_rays[i].dist * cos(tab_rays[i].angle -
			game->player.rot_angle);
		wall_height = game->dist_proj_plane / perp_dist;
		top_pixel = (game->win.height / 2.0) - ((int)wall_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		bot_pixel = (game->win.height / 2) + ((int)wall_height / 2);
		if (bot_pixel > game->win.height)
			bot_pixel = game->win.height;
		tab_rays[i].top_pixel = top_pixel;
		tab_rays[i].bot_pixel = bot_pixel;
		show_line(game, i, tab_rays[i], wall_height);
		i++;
	}
}

int					render(t_game *game)
{
	cast_all_rays(game);
	gen_3d(game, game->tab_rays);
	if (game->is_minimap)
	{
		render_map(game);
		render_ray_map(game, game->tab_rays);
		render_player(game);
	}
	scan_sprite(game);
	if (!game->save)
		mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
	game->win.image.img, 0, 0);
	return (TRUE);
}
