/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:54:11 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 00:56:02 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_sprites(t_cub3d *cub3d, int i, int x, int y)
{
	cub3d->sprites[i].coord.x = x + 0.5;
	cub3d->sprites[i].coord.y = y + 0.5;
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

/*
void	is_visible(t_cub3d *cub3d, int i)
{
	printf("sprit is vis ang? : %f\n", cub3d->sprites[i].ang);
	if (cub3d->sprites[i].ang > M_PI)
		cub3d->sprites[i].ang -= M_PI * 2;
	if (cub3d->sprites[i].ang < -M_PI)
		cub3d->sprites[i].ang += M_PI * 2;
	cub3d->sprites[i].ang = fabs(cub3d->sprites[i].ang);
	printf("ang after if? : %f\n", cub3d->sprites[i].ang);
	if(cub3d->sprites[i].ang < (FOV / 2))
		cub3d->sprites[i].visibility = 1;
	else
		cub3d->sprites[i].visibility = 0;
}*/
/*
   float	find_angle(t_cub3d *cub3d, int i)
   {
   return(cub3d->player.rot_ang - atan2(cub3d->sprites[i].coord.y - cub3d->player.pos.y, cub3d->sprites[i].coord.x - cub3d->player.pos.x));
   }
   */

   int	 is_visible(float angle_sprite)
   {
	printf("sprit is vis ang? : %f\n", angle_sprite);
   if (angle_sprite < -M_PI)
   angle_sprite += 2 * M_PI;
   if (angle_sprite >= M_PI)
   angle_sprite -= 2 * M_PI;
  // if (angle_sprite < 0)
  // angle_sprite = -angle_sprite;
	printf("fov / 2 : %f\n", FOV/2);
	printf("ang after if? : %f\n", angle_sprite);
   return (angle_sprite < (FOV / 2));
   }


float	find_angle(t_cub3d *cub3d, int i)
{
	float			dx;
	float			dy;
	float			angle;

	printf("sprites x : %f\n", cub3d->sprites[i].coord.x);
	printf("sprites y : %f\n", cub3d->sprites[i].coord.y);
    printf("player y : %f\n", cub3d->player.pos.x);
    printf("player x : %f\n", cub3d->player.pos.y);


	dx = cub3d->sprites[i].coord.x - cub3d->player.pos.x;
	dy = cub3d->sprites[i].coord.y - cub3d->player.pos.y;
	angle = atan2(dy, dx) - cub3d->player.rot_ang;
	return (angle);
}

float			distance(t_coord a, t_coord b)
{
	if (a.x >= 0 && b.x >= 0)
		return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
	else
		return (FLT_MAX);
}

void	fill_sprites(t_cub3d *cub3d, int i)
{
	//cub3d->sprites[i].distance = p_dist(cub3d->player.pos.x, cub3d->player.pos.y, cub3d->sprites[i].coord.x, cub3d->sprites[i].coord.y);
	cub3d->sprites[i].distance = distance(cub3d->player.pos, cub3d->sprites[i].coord);
	cub3d->sprites[i].ang =  find_angle(cub3d, i);
//	is_visible(cub3d, i);
	cub3d->sprites[i].visibility =  is_visible(cub3d->sprites[i].ang);
	printf("sprites vis : %d\n", cub3d->sprites[i].visibility);
}

void	render_sprites(t_cub3d *cub3d)
{
	int i;

	i = -1;
	while(++i < cub3d->data.num_sprites)
	{
		fill_sprites(cub3d, i);
		minimap_sprites(cub3d, i);
	printf("sprites x : %f\n", cub3d->sprites[i].coord.x);
	printf("sprites y : %f\n", cub3d->sprites[i].coord.y);
	printf("sprites ang : %f\n", cub3d->sprites[i].ang);
	printf("player ang : %f\n", cub3d->player.rot_ang);
	printf("sprites dist : %f\n", cub3d->sprites[i].distance);
//	printf("sprites hei : %d\n", cub3d->sprites[i].hei);
//	printf("sprites id : %d\n", cub3d->sprites[i].id);
//	printf("sprites firstx : %d\n", cub3d->sprites[i].first_x);
//	printf("sprites botp : %d\n", cub3d->sprites[i].bot_pixel);
//	printf("sprites topp : %d\n", cub3d->sprites[i].top_pixel);
	}
}
