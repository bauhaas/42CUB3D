/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/13 17:50:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** gcc -I /usr/local/include test.c key_events.c minimap.c init.c -L /usr/local/lib -lmlx -lXext -lX11
*/

#include "cub3d.h"

const int grid[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};


void update(t_cub3d *cub3d)
{

	int mov_step;

	cub3d->player.rot_ang += cub3d->player.turn_d * cub3d->player.rot_speed;
	
	//move player dot
	mov_step = cub3d->player.walk_d * cub3d->player.mov_speed;
	cub3d->player.x += cos(cub3d->player.rot_ang) * mov_step;
	cub3d->player.y += sin(cub3d->player.rot_ang) * mov_step;

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
	init_img(&cub3d->img, &cub3d->win);
	render_minimap(cub3d);	
	render_player(cub3d);
	mlx_put_image_to_window(cub3d->win.mlx_p, cub3d->win.win_p, cub3d->img.img, 10, 10);
}

int main()
{
	t_cub3d		cub3d;

	//INIT
	init_win(&cub3d.win);
	cub3d.win.mlx_p = mlx_init();
	cub3d.win.win_p = mlx_new_window(cub3d.win.mlx_p, 1000, 1000, "cub3d");
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
