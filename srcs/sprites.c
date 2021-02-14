/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:54:11 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 19:38:45 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_sprites(t_cub3d *cub3d, int i, int x, int y)
{
	cub3d->sprites[i].coord.x = x + 0.001;
	cub3d->sprites[i].coord.y = y + 0.001;
	cub3d->sprites[i].distance = -1;
	cub3d->sprites[i].ang = 0;
	cub3d->sprites[i].texture = 0;
	cub3d->sprites[i].visibility = 0;
}

void free_sprite(t_cub3d *cub3d)
{
	free(cub3d->sprites);
	cub3d->sprites = NULL;
}

int load_sprites(t_cub3d *cub3d)
{
	int i;
	int j;
	int id;

	i = -1;
	id = 0;
	while(++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			if(cub3d->grid[i][j] == '2' && id < cub3d->data.num_sprites)
			{
				init_sprites(cub3d, id, j, i);
				id++;
			}
		}
	}
	return (1);
}

void num_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub3d->data.rows)
	{
		j = -1;
		while (++j < cub3d->data.cols)
		{
			if (cub3d->grid[i][j] == '2')
				cub3d->data.num_sprites++;
		}
	}
}

int check_sprites(t_cub3d *cub3d)
{
	num_sprites(cub3d);
	cub3d->sprites = malloc(sizeof(t_sprite) * cub3d->data.num_sprites);
	if(!cub3d)
		return(is_error("Fail malloc for sprites"));
	return(1);
}


void	is_visible(t_cub3d *cub3d, int i)
{
	float angle;

	angle = cub3d->sprites[i].ang;
	//printf("sprit is vis ang? : %f\n", cub3d->sprites[i].ang);
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;
	angle = abs(angle);
//	printf("ang after if? : %f\n", angle);
	if(angle < (FOV / 2))
		cub3d->sprites[i].visibility = 1;
	else
		cub3d->sprites[i].visibility = 0;
}
/*
   float	find_angle(t_cub3d *cub3d, int i)
   {
   return(cub3d->player.rot_ang - atan2(cub3d->sprites[i].coord.y - cub3d->player.pos.y, cub3d->sprites[i].coord.x - cub3d->player.pos.x));
   }
   */
/*
   int	 is_visible(float angle_sprite)
   {
//	printf("sprit is vis ang? : %f\n", angle_sprite);
   if (angle_sprite < -M_PI)
   angle_sprite += 2 * M_PI;
   if (angle_sprite >= M_PI)
   angle_sprite -= 2 * M_PI;
   if (angle_sprite < 0)
   angle_sprite = -angle_sprite;
//	printf("fov / 2 : %f\n", FOV/2);
//	printf("ang after if? : %f\n", angle_sprite);
   return (angle_sprite < (FOV / 2));
   }
*/

float	find_angle(t_cub3d *cub3d, int i)
{
	float			dx;
	float			dy;
	float			angle;

//	printf("sprites x : %f\n", cub3d->sprites[i].coord.x);
//	printf("sprites y : %f\n", cub3d->sprites[i].coord.y);
//  printf("player y : %f\n", cub3d->player.pos.x);
 //printf("player x : %f\n", cub3d->player.pos.y);
	dx = cub3d->sprites[i].coord.x - cub3d->player.pos.x;
	dy = cub3d->sprites[i].coord.y - cub3d->player.pos.y;
	angle = atan2(dy, dx) - cub3d->player.rot_ang;
	return (angle);
}
/*
float			distance(t_coord a, t_coord b)
{
	if (a.x >= 0 && b.x >= 0)
		return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
	else
		return (FLT_MAX);
}*/

void	fill_sprites(t_cub3d *cub3d, int i)
{
	cub3d->sprites[i].distance = p_dist(cub3d->player.pos.x, cub3d->player.pos.y, cub3d->sprites[i].coord.x, cub3d->sprites[i].coord.y);
	//cub3d->sprites[i].distance = distance(cub3d->player.pos, cub3d->sprites[i].coord);
	cub3d->sprites[i].ang =  find_angle(cub3d, i);
	is_visible(cub3d, i);
//	cub3d->sprites[i].visibility =  is_visible(cub3d->sprites[i].ang);
}


void draw_sprite(t_cub3d *cub3d, t_sprite sprite, t_coord pos,
					t_coord offset)
{
	int				color;
	int				no_color;

	no_color = grep_color(cub3d->text[4], 0, 0);
	offset.y = (pos.y + (sprite.hei / 2.0) - (cub3d->win.hei / 2.0)) *
	(cub3d->text[4].hei / sprite.hei);
	if (offset.y < 0)
		offset.y = 0;
	color = grep_color(cub3d->text[4], offset.x, offset.y);
	/*
	printf("draw color : %d\n", color);
	printf("draw no_color : %d\n", no_color);
	printf("draw offset x : %f\n", offset.x);
	printf("draw offset y : %f\n", offset.y);
	printf("draw pos x : %f\n", pos.x);
	printf("draw pos y : %f\n", pos.y);
	*/
	if (color != no_color)
		my_mlx_pixel_put(&cub3d->win, sprite.first_x + pos.x, pos.y, color);
}

void	render_sprite(t_cub3d *cub3d, t_sprite sprite)
{
	t_coord			point;
	t_coord			offset;
	float			dist_ray;

	point.x = -1;
	while (sprite.first_x + point.x < 0)
		point.x++;
//	printf("offset x, %f\n", offset.x);
//	printf("sprite hei, %f\n", sprite.hei);
//	printf("point x, %f\n", point.x);
	while (++point.x < sprite.hei && sprite.first_x + point.x < cub3d->win.wid)
	{
		dist_ray = cub3d->rays[(int)(sprite.first_x + point.x)].distance;
		if (dist_ray > cub3d->sprites[sprite.id].distance)
		{
			offset.x = point.x * cub3d->text[4].wid / sprite.hei;
			point.y = sprite.top_pixel - 1;
			while (++point.y < sprite.bot_pixel)
				draw_sprite(cub3d, sprite, point, offset);
		}
	}
}

static void			sprite_data(t_cub3d *cub3d, t_sprite *sprite)
{
	int				i;
	int				top;
	int				bot;

	i = -1;
	while (++i < cub3d->data.num_sprites)
	{
		if (sprite[i].visibility)
		{
			sprite[i].id = i;
			sprite[i].hei = (cub3d->data.dist_proj_plane) /
			(cos(sprite[i].ang) * sprite[i].distance);
			top = (cub3d->win.hei / 2.0) - (sprite[i].hei / 2);
			if (top < 0)
				top = 0;
			bot = (cub3d->win.hei / 2.0) + (sprite[i].hei / 2);
			if (bot > cub3d->win.hei)
				bot = cub3d->win.hei;
			sprite[i].top_pixel = top;
			sprite[i].bot_pixel = bot;
			sprite[i].first_x = cub3d->data.dist_proj_plane * tan(sprite[i].ang)
			+ (cub3d->win.wid / 2) - (sprite[i].hei / 2);
//	printf("top pixel : %d\n", sprite[i].top_pixel);
//	printf("bot pixel : %d\n", sprite[i].bot_pixel);
//	printf("first x : %f\n", sprite[i].first_x);
			render_sprite(cub3d, sprite[i]);
		}
	}
}

void	render_sprites(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while(++i < cub3d->data.num_sprites)
	{
		fill_sprites(cub3d, i);
		//minimap_sprites(cub3d, i);
//	printf("sprites vis : %d\n", cub3d->sprites[i].visibility);
//	printf("sprites x : %f\n", cub3d->sprites[i].coord.x);
//	printf("sprites y : %f\n", cub3d->sprites[i].coord.y);
//	printf("sprites ang : %f\n", cub3d->sprites[i].ang);
//	printf("player ang : %f\n", cub3d->player.rot_ang);
//	printf("sprites dist : %f\n", cub3d->sprites[i].distance);
//	printf("sprites hei : %d\n", cub3d->sprites[i].hei);
//	printf("sprites id : %d\n", cub3d->sprites[i].id);
//	printf("sprites firstx : %d\n", cub3d->sprites[i].first_x);
//	printf("sprites botp : %d\n", cub3d->sprites[i].bot_pixel);
//	printf("sprites topp : %d\n", cub3d->sprites[i].top_pixel);
	}
	sprite_data(cub3d, cub3d->sprites);
}
