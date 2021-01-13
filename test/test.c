/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:37:21 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/13 02:43:26 by bahaas           ###   ########.fr       */
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

/*
void update(t_player *player)
{
	player->rot_ang += player->turn_d * player->rot_speed;
}

void render(t_player *player)
{
	init_player(player);
	update(player);
}
*/

void	render_minimap(t_img *img)
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
				render_minimap_wall_square(j + j_pix_pos, i + i_pix_pos, MINI_SIZE, img);
			}
			j_pix_pos += MINI_SIZE;
			j++;
		}
		i++;
		i_pix_pos += MINI_SIZE;
	}
}

int main()
{
	t_img		img;
	t_win		win;
	t_player	player;
	t_map		map;

	win.mlx_p = mlx_init();
	win.win_p = mlx_new_window(win.mlx_p, 500, 500, "cub3d");

	//init_win(&win);
	init_img(&img, &win);
	init_player(&player);
	init_map(&map);

	render_minimap(&img);
	render_player(&img, &player);

	//KEY EVENTS
	mlx_hook(win.win_p, 2, 1L<<0, key_pressed, &player);
	mlx_hook(win.win_p, 3, 1L<<1, key_released, &player);

	///DISPLAY ALL
	mlx_put_image_to_window(win.mlx_p, win.win_p, img.img, 10, 10);
	mlx_loop(win.mlx_p);
}
