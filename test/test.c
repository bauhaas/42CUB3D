/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/26 17:26:06 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if(!grid_is_wall(new_player_x, new_player_y, cub3d))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
}

void		rect(float x, float y, float x2, float y2, t_cub3d *cub3d)
{
	int			i;
	int			j;

	j = 0;
	while (j < x2)
	{
		i = 0;
		while (i < y2)
		{
			my_mlx_pixel_put(&cub3d->img, x + j, y + i, WHITE);
			i++;
		}
		j++;
	}
}

void	render_3d_walls(t_ray *rays, t_cub3d *cub3d)
{
	int i;
	int wall_strip_height;
	float correct_fisheye_distance;
	float distance_projection_plane;
	float ray_distance;
	i = 0;
	while(i < NUM_RAYS)
	{
	//	distance_projection_plane = (WIN_WID / 2) / tan(FOV / 2);
		ray_distance = rays[i].distance;
		correct_fisheye_distance = rays[i].distance * cos(rays[i].ray_ang - cub3d->player.rot_ang);
		wall_strip_height = (TILE_SIZE / correct_fisheye_distance) * DIST_PROJ_PLANE;
	//	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
		rect((i * WALL_STIP_WIDTH), ((WIN_HEI / 2) - (wall_strip_height / 2)), WALL_STIP_WIDTH, wall_strip_height, cub3d);
		i++;
	}
}

void	render(t_cub3d *cub3d)
{
	t_ray *rays;

	init_img(&cub3d->img, &cub3d->win);
	update(cub3d);
	rays = cast_all_rays(cub3d);
	render_3d_walls(rays, cub3d);
	render_minimap(cub3d);	
	free(rays);
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
