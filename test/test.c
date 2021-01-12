//gcc -i /usr/local/include test.c -L /usr/local/lib -lmlx -lXext -lX11

#include "mlx.h"
#include <stdio.h>
#include <math.h>

const int MINIMAP_SIZ = 20;
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

typedef struct s_player {
	int x;
	int y;
	int radius;
	int turn_direction; // = 0; //left = -1, right = 1
	int walk_direction; //= 0; //back = -1, front = 1
	int rotation_angle; //= M_PI / 2;
	int rotation_speed; //= 3 * (M_PI / 180);
	int move_speed; // = 3;
}				t_player;

void init_player(t_player *player)
{
	player->x = 2;
	player->y = 2;
	player->radius = 9;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI / 2;
	player->rotation_speed = 2 * (M_PI / 180);
	player->move_speed = 2;
}

typedef struct s_data {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}				t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

typedef struct s_params {
	void *mlx;
	void *win;
}				t_params;

/*
int key_hook(int keycode, void *win_ptr, void *mlx_ptr)
{
	printf("Hello\n");
}
*/
int key_pressed(int keycode, t_player *player)
{
	if(keycode == 'w')
	{
		player->walk_direction = 1;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->walk_direction);
	}
	else if(keycode == 's')
	{
		player->walk_direction = -1;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->walk_direction);
	}
	if(keycode == 'a')
	{
		player->turn_direction = -1;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->turn_direction);
	}
	if(keycode == 'd')
	{
		player->turn_direction = 1;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->turn_direction);
	}
}

int key_released(int keycode, t_player *player)
{
	if(keycode == 'w')
	{
		player->walk_direction = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->walk_direction);
	}
	else if(keycode == 's')
	{
		player->walk_direction = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->walk_direction);
	}
	if(keycode == 'a')
	{
		player->turn_direction = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->turn_direction);
	}
	if(keycode == 'd')
	{
		player->turn_direction = 0;
		printf("keycode : %d\n", keycode);
		printf("walk_direction : %d\n", player->turn_direction);
	}
}

/*
int close(int keycode, t_params *params)
{
	mlx_destroy_window(params->mlx, params->win);
}
*/

void minimap_draw(int x, int y, int size, t_data *img)
{
	int j = 0;
	int i = 0;

	while(i < size)
	{
		j = 0;
		while(j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, 0x00FF00);
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
		my_mlx_pixel_put(img, x + 4.5 + j, y + 4.5 + i, 0x00FF0000);
		i++;
	}

}

void draw_player(t_data *img, t_player *player)
{
	int x = player->x;
	int y = player->y;

	minimap_draw(x * MINIMAP_SIZ/2 + 10, y * MINIMAP_SIZ/2 + 10, player->radius, img);
	view_line_draw(x * MINIMAP_SIZ/2 + 10, y * MINIMAP_SIZ/2 + 10, 20, img);
}

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
				minimap_draw(j + j_pix_pos, i + i_pix_pos, MINIMAP_SIZ, &img);
			}
			j_pix_pos += MINIMAP_SIZ;
			j++;
		}
		i++;
		i_pix_pos += MINIMAP_SIZ;
	}
	//// EOF OF MINIMAP
	////
	init_player(&player);
	draw_player(&img, &player);

	
	mlx_put_image_to_window(params.mlx, params.win, img.img, 10, 10);

 	//mlx_key_hook(params.win, key_hook, &params);
 	//mlx_key_hook(params.win, key_pressed, &player);
	mlx_hook(params.win, 2, 1L<<0, key_pressed, &player);
	mlx_hook(params.win, 3, 1L<<1, key_released, &player);
	mlx_loop(params.mlx);
}

//keycode 25 w
//a 38
//s 39
//d 40
