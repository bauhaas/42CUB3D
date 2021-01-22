/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/22 14:44:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	cast(t_ray *ray, t_cub3d *cub3d)
{
	float xstep;
	float ystep;
	float xintercept;
	float yintercept;

	//////
	////// HORIZONTAL
	//////
	int found_hor_wall = 0;
	float hz_wall_hit_x = 0;
	float hz_wall_hit_y = 0;

	//printf("right: %d\n", ray->facing_right);
	//printf("left : %d\n", ray->facing_left);
	//printf("up :   %d\n", ray->facing_up);
	//printf("down : %d\n\n", ray->facing_down);
	//printf("ray_ang : %f\n\n", ray->ray_ang);
	//HORITZONTAL  ->
	yintercept = floor(cub3d->player.pos.y / TILE_SIZE) * TILE_SIZE; //minisize = tilesize
	yintercept +=  ray->facing_down ? TILE_SIZE : 0;
	// find x coordinate of the closest horizontal grid intersec
	xintercept = cub3d->player.pos.x + (yintercept - cub3d->player.pos.y) / tan(ray->ray_ang);

	//printf("yintercept : %f\n", yintercept);
	//printf("playerx : %f\n", cub3d->player.pos.x);
	//printf("playery : %f\n", cub3d->player.pos.y);
	//printf("xintercept : %f\n", xintercept);
	//calculate incre;ent of xstep and ystep
	ystep = TILE_SIZE;
	ystep *= ray->facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray->ray_ang);
	xstep *= (ray->facing_left && xstep > 0) ? -1 : 1;
	xstep *= (ray->facing_right && xstep < 0) ? -1 : 1;
	
	//printf("y_step : %f\n", ystep);
	//printf("x_step : %f\n", xstep);
	float hz_next_hor_x = xintercept;
	float hz_next_hor_y = yintercept;

	//printf("hz_next_hor_x : %f\n", hz_next_hor_x);
	t_line vline;

	if(ray->facing_up)
		hz_next_hor_y--;
	//printf("hz_next_hor_y : %f\n", hz_next_hor_y);
	//increment xstep and ystep till a wall is find
	while(hz_next_hor_x >= 0 && hz_next_hor_x <= WIN_WID && hz_next_hor_y >= 0 && hz_next_hor_y <= WIN_HEI)
	{
		if(grid_is_wall(hz_next_hor_x, hz_next_hor_y, cub3d))
		{
			//we found wall
			hz_wall_hit_y = hz_next_hor_y;
			hz_wall_hit_x = hz_next_hor_x;
			//printf("loop hz_next_hor_y : %f\n", hz_next_hor_y);
			//printf("loop hz_next_hor_x : %f\n", hz_next_hor_x);
			//printf("wallhitx : %f\n", hz_wall_hit_x);
			//printf("wallhity : %f\n", hz_wall_hit_y);
			found_hor_wall = 1;
			
			//vline.start.x = cub3d->player.pos.x;
			//vline.start.y = cub3d->player.pos.y;
			//vline.end.x = hz_wall_hit_x;
			//vline.end.y = hz_wall_hit_y;
			//render_view_line(&vline, cub3d, GREEN);
			break;
		}
		else
		{
			hz_next_hor_x += xstep;
			hz_next_hor_y += ystep;
			//printf("test\n");
		}
	}
	
	//VERTICAL
	//VERTICAL
	//VERTICAL
	//VERTICAL
	int found_ver_wall = 0;
	float vt_wall_hit_x = 0;
	float vt_wall_hit_y = 0;

	//printf("right: %d\n", ray->facing_right);
	//printf("left : %d\n", ray->facing_left);
	//printf("up :   %d\n", ray->facing_up);
	//printf("down : %d\n\n", ray->facing_down);
	//printf("ray_ang : %f\n\n", ray->ray_ang);
	xintercept = floor(cub3d->player.pos.x / TILE_SIZE) * TILE_SIZE; //minisize = tilesize
	xintercept +=  ray->facing_right ? TILE_SIZE : 0;
	// find x coordinate of the closest horizontal grid intersec
	yintercept = cub3d->player.pos.y + (xintercept - cub3d->player.pos.x) * tan(ray->ray_ang);

	//printf("yintercept : %f\n", yintercept);
	//printf("playerx : %f\n", cub3d->player.pos.x);
	//printf("playery : %f\n", cub3d->player.pos.y);
	//printf("xintercept : %f\n", xintercept);
	//calculate incre;ent of xstep and ystep
	xstep = TILE_SIZE;
	xstep *= ray->facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray->ray_ang);
	ystep *= (ray->facing_up && ystep > 0) ? -1 : 1;
	ystep *= (ray->facing_down && ystep < 0) ? -1 : 1;
	
	//printf("y_step : %f\n", ystep);
	//printf("x_step : %f\n", xstep);
	float vt_next_hor_x = xintercept;
	float vt_next_hor_y = yintercept;

	//printf("vt_next_hor_x : %f\n", vt_next_hor_x);
	t_line line;

	if(ray->facing_left)
		vt_next_hor_x--;
	//printf("vt_next_hor_y : %f\n", vt_next_hor_y);
	//increment xstep and ystep till a wall is find
	while(vt_next_hor_x >= 0 && vt_next_hor_x <= WIN_WID && vt_next_hor_y >= 0 && vt_next_hor_y <= WIN_HEI)
	{
		if(grid_is_wall(vt_next_hor_x, vt_next_hor_y, cub3d))
		{
			//we found wall
			vt_wall_hit_y = vt_next_hor_y;
			vt_wall_hit_x = vt_next_hor_x;
			//printf("loop vt_next_hor_y : %f\n", vt_next_hor_y);
			//printf("loop vt_next_hor_x : %f\n", vt_next_hor_x);
			//printf("wallhitx : %f\n", vt_wall_hit_x);
			//printf("wallhity : %f\n", vt_wall_hit_y);
			found_ver_wall = 1;
			
			//line.start.x = cub3d->player.pos.x;
			//line.start.y = cub3d->player.pos.y;
			//line.end.x = vt_wall_hit_x;
			//line.end.y = vt_wall_hit_y;
			//render_view_line(&line, cub3d, GREEN);
			break;
		}
		else
		{
			vt_next_hor_x += xstep;
			vt_next_hor_y += ystep;
			//printf("test\n");
		}
	}


	// find both hw and vt distance and choos the smallest value
	float hz_distance = (found_hor_wall)
		? distance_points(cub3d->player.pos.x, cub3d->player.pos.y, hz_wall_hit_x, hz_wall_hit_y)
		: FLT_MAX;
			printf("hz_dist : %f\n", hz_distance);
	float vt_distance = (found_ver_wall)
		? distance_points(cub3d->player.pos.x, cub3d->player.pos.y, vt_wall_hit_x, vt_wall_hit_y)
		: FLT_MAX;
			printf("vt_dist : %f\n", vt_distance);
	ray->wall_hit_x = (hz_distance < vt_distance) ? hz_wall_hit_x : vt_wall_hit_x;
		//	printf("wall_hit_x : %f\n", ray->wall_hit_x);
	ray->wall_hit_y = (hz_distance < vt_distance) ? hz_wall_hit_y : vt_wall_hit_y;
		//	printf("wall_hit_y : %f\n", ray->wall_hit_y);
	ray->distance = (hz_distance < vt_distance) ? hz_distance : vt_distance;
			printf("distance : %f\n", ray->distance);
	ray->was_vt_hit = (vt_distance < hz_distance);
		//	printf("was_vt_hit : %d\n", ray->was_vt_hit);

			line.start.x = cub3d->player.pos.x;
			line.start.y = cub3d->player.pos.y;
			line.end.x = ray->wall_hit_x;
			line.end.y = ray->wall_hit_y;
			render_view_line(&line, cub3d, GREEN);
}
*/

void update(t_cub3d *cub3d)
{
	float mov_step;
	float new_player_x;
	float new_player_y;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	cub3d->player.rot_ang = normalize(cub3d->player.rot_ang);

	//move player dot
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	new_player_x = cub3d->player.pos.x + cos(cub3d->player.rot_ang) * mov_step;
	new_player_y = cub3d->player.pos.y + sin(cub3d->player.rot_ang) * mov_step;

	//BONUS COLLISION
	//NEED TO BE FIXED 

	if(!grid_is_wall(new_player_x, new_player_y, cub3d))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
	//printf("new rot ang : %f\n", cub3d->player.rot_ang);
	//render(cub3d);
}

void	render(t_cub3d *cub3d)
{
	int i = 0;

	init_img(&cub3d->img, &cub3d->win);
	update(cub3d);
	render_minimap(cub3d);	
	cub3d->rays = cast_all_rays(cub3d);
	//while(i < NUM_RAYS)
	//{
	//render_ray(cub3d, i);
	//	i++;
	//}
	free(cub3d->rays);
	render_player(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->img.img, 0, 0);
}

int main()
{
	t_cub3d		cub3d;
	char		**grid;
	
	//INIT
	init_win(&cub3d.win);
	cub3d.win.mlx_p = mlx_init();
	cub3d.win.win_p = mlx_new_window(cub3d.win.mlx_p, WIN_WID, WIN_HEI, "cub3d");
	init_img(&cub3d.img, &cub3d.win);
	init_player(&cub3d.player);
	init_map(&cub3d.map);

	grid =  malloc(sizeof(char*) * 11);
	grid[0] = "111111111111111";
	grid[1] = "100000000000101";
	grid[2] = "100001000000101";
	grid[3] = "111100000010101";
	grid[4] = "100000000010101";
	grid[5] = "100000001111101";
	grid[6] = "100000000000001";
	grid[7] = "100000000000001";
	grid[8] = "111111100111101";
	grid[9] = "100000000000001";
	grid[10] = "111111111111111";
	cub3d.grid = grid;
	
	//RENDER
	render(&cub3d);

	printf("RAYS NuMBERS :%d\n", NUM_RAYS);
	//KEY EVENTS
	mlx_hook(cub3d.win.win_p, 2, 1L<<0, key_pressed, &cub3d);
	mlx_hook(cub3d.win.win_p, 3, 1L<<1, key_released, &cub3d.player);

	mlx_loop(cub3d.win.mlx_p);
}
