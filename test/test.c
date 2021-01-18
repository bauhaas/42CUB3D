/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/16 16:49:56 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** gcc -I /usr/local/include test.c key_events.c minimap.c init.c -L /usr/local/lib -lmlx -lXext -lX11
*/

#include "cub3d.h"

const int grid[10][10] = {
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};


t_ray *cast_all_rays(t_cub3d *cub3d)
{
	t_ray	*rays;
	float	ray_ang;
	int i;

	i = 0;
	rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if(!rays)
		return 0;
	ray_ang = cub3d->player.rot_ang - FOV / 2;
	while(i < NUM_RAYS)
	{
		rays[i].ray_ang = ray_ang;
		ray_ang += FOV / NUM_RAYS;
		i++;
	}
	return(rays);
}

int grid_is_wall(int x, int y)
{
	int grid_x = x / MINI_SIZE;
	int grid_y = y / MINI_SIZE;
	//win borders
	if(x < 0 || x > WIN_WID || y < 0 || y > WIN_HEI)
		return TRUE;
	//minimap borders
	// TO FIX : player pixel appear just after border
	if(grid_x >= MAP_COLS || grid_y >= MAP_ROWS)
		return TRUE;
	return(grid[grid_y][grid_x] != 0);
}

void update(t_cub3d *cub3d)
{
	int mov_step;
	int new_player_x;
	int new_player_y;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	
	//move player dot
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	new_player_x = cub3d->player.pos.x + cos(cub3d->player.rot_ang) * mov_step;
	new_player_y = cub3d->player.pos.y + sin(cub3d->player.rot_ang) * mov_step;

	//BONUS COLLISION
	//NEED TO BE FIXED 
	
	if(!grid_is_wall(new_player_x, new_player_y))
	{
		cub3d->player.pos.x = new_player_x;
		cub3d->player.pos.y = new_player_y;
	}
	
	printf("new rot ang : %f\n", cub3d->player.rot_ang);
	render(cub3d);
}

void	render_minimap(t_cub3d *cub3d)
{
	int i = 0;
	int j = 0;
	int i_pix_pos = 0;
	int j_pix_pos = 0;

	while (i < MAP_ROWS )
	{
		j = 0;
		j_pix_pos = 0;
		while (j < MAP_COLS)
		{
			if (grid[i][j] == 1)
			{
				render_minimap_square(j + j_pix_pos, i + i_pix_pos, MINI_SIZE, cub3d);
			}
			j_pix_pos += MINI_SIZE;
			j++;
		}
		i++;
		i_pix_pos += MINI_SIZE;
	}
}

void	render(t_cub3d *cub3d)
{
	t_ray *rays;
	int i = 0;

	init_img(&cub3d->img, &cub3d->win);
	render_minimap(cub3d);	
	render_player(cub3d);
	rays = cast_all_rays(cub3d);
	while(i < NUM_RAYS)
	{
		render_ray(cub3d, rays[i]);
		i++;
	}
	free(rays);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->img.img, 0, 0);
}

int main()
{
	t_cub3d		cub3d;

	//INIT
	init_win(&cub3d.win);
	cub3d.win.mlx_p = mlx_init();
	cub3d.win.win_p = mlx_new_window(cub3d.win.mlx_p, WIN_WID, WIN_HEI, "cub3d");
	init_img(&cub3d.img, &cub3d.win);
	init_player(&cub3d.player);
	init_map(&cub3d.map);

	//RENDER
	render(&cub3d);

	//KEY EVENTS
	mlx_hook(cub3d.win.win_p, 2, 1L<<0, key_pressed, &cub3d);
	mlx_hook(cub3d.win.win_p, 3, 1L<<1, key_released, &cub3d.player);

	mlx_loop(cub3d.win.mlx_p);
}
