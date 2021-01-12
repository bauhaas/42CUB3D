//gcc -i /usr/local/include test.c key_events.c -L /usr/local/lib -lmlx -lXext -lX11

#include "cub3d.h"

const int MAP_ROWS = 10;
const int MAP_COLS = 10;

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

void init_player(t_player *player)
{
	player->x = 2;
	player->y = 2;
	player->radius = 9;
	player->turn_d = 0;
	player->walk_d = 0;
	player->rot_ang = M_PI / 2;
	player->rot_speed = 2 * (M_PI / 180);
	player->mov_speed = 2;
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void minimap_draw(int x, int y, int size, t_data *img)
{
	int j = 0;
	int i = 0;

	while(i < size)
	{
		j = 0;
		while(j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, GRAY);
			j++;
		}
		i++;
	}
}

void view_line_draw(int x, int y, int size, t_data *img)
{
	int j = 0;
	int i = 0;

	while(i < size)
	{
		my_mlx_pixel_put(img, x + 4.5 + j, y + 4.5 + i, WHITE);
		i++;
	}

}
/*
void draw_player(t_data *img, t_player *player)
{
	int x = player->x;
	int y = player->y;

	minimap_draw(x * MINI_SIZE/2 + 10, y * MINI_SIZE/2 + 10, player->radius, img);
	view_line_draw(x * MINI_SIZE/2 + 10, y * MINI_SIZE/2 + 10, 20, img);
}*/

int main()
{
	void *img_ptr;
	t_data img;
	t_params params;
	t_player player;

	///INIT WINDOW
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, 500, 500, "cub3d");
	img.img = mlx_new_image(params.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	/// BEGIN OF MINIMAP
	int i = 0;
	int j = 0;
	int i_pix_pos = 0;
	int j_pix_pos = 0;
	while(i < MAP_ROWS )
	{
		j = 0;
		j_pix_pos = 0;
		while(j < MAP_COLS)
		{
			if(grid[i][j] == 1)
			{
				minimap_draw(j + j_pix_pos, i + i_pix_pos, MINI_SIZE, &img);
			}
			j_pix_pos += MINI_SIZE;
			j++;
		}
		i++;
		i_pix_pos += MINI_SIZE;
	}
	//// EOF OF MINIMAP
	//// PLAYER DISPLAY
	init_player(&player);
	draw_player(&img, &player);

	/// DISLAY ALL
	mlx_put_image_to_window(params.mlx, params.win, img.img, 10, 10);

	//KEY EVENTS
	mlx_hook(params.win, 2, 1L<<0, key_pressed, &player);
	mlx_hook(params.win, 3, 1L<<1, key_released, &player);
	//rendering()
	mlx_loop(params.mlx);
}

//keycode 25 w
//a 38
//s 39
//d 40
