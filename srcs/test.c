/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/12 19:49:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void update(t_cub3d *cub3d)
{
	float mov_step;
	float new_player_x;
	float new_player_y;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	//for sprite if too much rotation
	cub3d->player.rot_ang = normalize(cub3d->player.rot_ang);

	//move player dot
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	new_player_x = cub3d->player.pos.x + cos(cub3d->player.rot_ang) * mov_step;
	new_player_y = cub3d->player.pos.y + sin(cub3d->player.rot_ang) * mov_step;

	if (!grid_is_wall(new_player_x, new_player_y, cub3d))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
}

void		rect(float x, float y, float x2, float y2, t_cub3d *cub3d, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j < x2)
	{
		i = 0;
		while (i < y2)
		{
			my_mlx_pixel_put(&cub3d->win, x + j, y + i, color);
			i++;
		}
		j++;
	}
}


int					grep_color(t_text text, int x, int y)
{
	char			*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > text.wid)
		x = text.wid;
	if (y > text.hei)
		y = text.hei;
	dst = text.data + (y * text.line_length + x * text.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}


static void			render_line(t_cub3d *cub3d, int x, t_ray ray, float wall_height)
{
	int				i;
	int				off_x;
	int				off_y;
	int				color;

	i = 0;
	while (i < ray.top_pixel)
		my_mlx_pixel_put(&cub3d->win, x, i++, cub3d->data.ceil);
	if (ray.was_vt_hit)
		//off_x = (int)(fmod(ray.wall_hit_y, 1.0) * cub3d->text[0].wid);
		off_x = (int)(fmod(ray.wall_hit_y, 64));
	else
		//off_x = (int)(fmod(ray.wall_hit_x, 1.0) * cub3d->text[0].wid);
		off_x = (int)(fmod(ray.wall_hit_x, 64));
	while (i < ray.bot_pixel)
	{
		off_y = (i + (wall_height / 2.0) - (cub3d->win.hei / 2.0)) *
		(cub3d->text[0].hei / wall_height);
		color = grep_color(cub3d->text[ray.id], off_x, off_y);
		my_mlx_pixel_put(&cub3d->win, x, i++, color);
	}
	while (i < cub3d->win.hei)
		my_mlx_pixel_put(&cub3d->win, x, i++, cub3d->data.floor);
}

void				render_3d_walls(t_ray *rays, t_cub3d *cub3d)
{
	int				i;
	float			perp_dist;
	float			wall_height;
	int				top_pixel;
	int				bot_pixel;
	double			dist_proj_plane;

	dist_proj_plane = (cub3d->win.wid / 2) / (tan(FOV / 2));

	i = 0;
	while (i < cub3d->win.wid)
	{/*
		perp_dist = rays[i].distance * cos(rays[i].ray_ang -
			cub3d->player.rot_ang);
		wall_height = DIST_PROJ_PLANE / perp_dist;
		top_pixel = (cub3d->win.hei / 2.0) - ((int)wall_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		bot_pixel = (cub3d->win.hei / 2) + ((int)wall_height / 2);
		if (bot_pixel > cub3d->win.hei)
			bot_pixel = cub3d->win.hei;*/

/*
		perp_dist = rays[i].distance * cos(rays[i].ray_ang - cub3d->player.rot_ang);
		wall_height = (TILE_SIZE / perp_dist) * DIST_PROJ_PLANE;
		top_pixel = (cub3d->win.hei / 2) - (wall_height / 2);
		top_pixel = top_pixel < 0 ? 0 : top_pixel;
		bot_pixel = (cub3d->win.hei / 2) + (wall_height / 2);
		bot_pixel = bot_pixel > cub3d->win.hei ? cub3d->win.hei : bot_pixel;
		//ray_distance = rays[i].distance;
*/
		perp_dist = rays[i].distance * cos(rays[i].ray_ang -
			cub3d->player.rot_ang);
		//wall_height = (TILE_SIZE / perp_dist) * DIST_PROJ_PLANE;
		wall_height = (TILE_SIZE / perp_dist) * dist_proj_plane;
		//wall_height = DIST_PROJ_PLANE / perp_dist;
		//wall_height = dist_proj_plane / perp_dist;
		top_pixel = (cub3d->win.hei / 2.0) - ((int)wall_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		bot_pixel = (cub3d->win.hei / 2) + ((int)wall_height / 2);
		if (bot_pixel > cub3d->win.hei)
			bot_pixel = cub3d->win.hei;

		rays[i].top_pixel = top_pixel;
		rays[i].bot_pixel = bot_pixel;
		render_line(cub3d, i, rays[i], wall_height);
		i++;
	}
}

/*
static void			show_line(t_cub3d *cub3d, int x, t_ray rays, float wall_height, int top_pixel, int bot_pixel)
{
	int				i;
	int				off_x;
	int				off_y;
	int				color;

	i = 0;
	while (i < top_pixel)
	{
		my_mlx_pixel_put(&cub3d->win, x, i, BLUE);
		i++;
	}
	if (rays.was_vt_hit)
		off_x = (int)(fmod(rays.wall_hit_y, 1.0) * cub3d->text[2].wid);
	else
		off_x = (int)(fmod(rays.wall_hit_x, 1.0) * cub3d->text[2].wid);
	while (i < bot_pixel)
	{
		off_y = (i + (wall_height / 2.0) - (cub3d->win.hei / 2.0)) *
		(cub3d->text[0].hei / wall_height);
		color = grep_color(cub3d->text[2], off_x, off_y);
		my_mlx_pixel_put(&cub3d->win, x, i, color);
		i++;
	}
	while (i < cub3d->win.hei)
	{
		my_mlx_pixel_put(&cub3d->win, x, i, RED);
		i++;
	}
}
void	render_3d_walls(t_ray *rays, t_cub3d *cub3d)
{
	int		i;
	int		wall_strip_height;
	float	perp_distance;
	float	ray_distance;
	int top_pixel;
	int bot_pixel;
	t_line line;
	t_coord coord;
	t_coord coord2;

	int x;
	i = 0;
	top_pixel = 0;
	bot_pixel = 0;
	ray_distance = 0;
	perp_distance = 0;
	wall_strip_height = 0;
	while (i < cub3d->win.wid)
	{
		top_pixel = (cub3d->win.hei / 2) - (wall_strip_height / 2);
		top_pixel = top_pixel < 0 ? 0 : top_pixel;
		bot_pixel = (cub3d->win.hei / 2) + (wall_strip_height / 2);
		bot_pixel = bot_pixel > cub3d->win.hei ? cub3d->win.hei : bot_pixel;
		ray_distance = rays[i].distance;
		perp_distance = rays[i].distance * cos(rays[i].ray_ang - cub3d->player.rot_ang);
		wall_strip_height = (TILE_SIZE / perp_distance) * DIST_PROJ_PLANE;
		x = top_pixel;
		while (x < cub3d->win.hei) 
		{
			my_mlx_pixel_put(&cub3d->win, i, x, RED);
			x++;
		}
		int y = 0;
		while (y < top_pixel + 1)
		{
			my_mlx_pixel_put(&cub3d->win, i, y, BLUE);
			y++;
		}
		show_line(cub3d, i, rays[i], wall_strip_height, top_pixel, bot_pixel);
		i++;
		/*
		int off_x;
		int off_y;
		int text_color;
		   
		if (rays[i].was_vt_hit)
		   off_x = (int)fmod(rays[i].wall_hit_y, 1.0) * cub3d->text[0].wid;
		else
		   off_x = (int)fmod(rays[i].wall_hit_x, 1.0) * cub3d->text[0].wid;
		int j = 0;
		while(j < bot_pixel)
		{
		   off_y = (j + (wall_strip_height / 2) - (cub3d->win.hei / 2) * (cub3d->text[0].hei / wall_strip_height));
		   text_color = grep_color(cub3d->text[0], i, j);
		   my_mlx_pixel_put(&cub3d->win, x, j, text_color);
		   j++;
		}
		*/
//		i++;
//	}
//}

void	render(t_cub3d *cub3d)
{
	t_ray *rays;

	update(cub3d);
	rays = cast_all_rays(cub3d);
	//render_minimap(cub3d);	
	render_3d_walls(rays, cub3d);
	free(rays);
	//render_player(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->win.img.img, 0, 0);
}

void run_cub3d(t_cub3d *cub3d)
{
	load_win(&cub3d->win);
	load_img(&cub3d->win);
	mlx_hook(cub3d->win.win_p, 2, 1L<<0, key_pressed, cub3d);
	mlx_hook(cub3d->win.win_p, 3, 1L<<1, key_released, &cub3d->player);
	mlx_hook(cub3d->win.win_p, 33, 1L<<17, &end_cub3d, cub3d);
	render(cub3d);
	mlx_loop(cub3d->win.mlx_p);
}
