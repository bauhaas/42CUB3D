//gcc -i /usr/local/include test.c -L /usr/local/lib -lmlx -lXext -lX11

#include "mlx.h""
#include <stdio.h>

const int TILE_SIZE = 32;
const int MAP_ROWS = 10;
const int MAP_COLS = 10;

const int grid[10][10] = {
	{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

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

int close(int keycode, t_params *params)
{
	mlx_destroy_window(params->mlx, params->win);
}
*/

void minimap_borders(int x, int y, int size, t_data *img)
{
	int i = 0;
	int j = 0;

	while(j <= size)
	{
		i = 0;
		while(i <= size)
		{
			my_mlx_pixel_put(img, x + i, y, 0x00FF00); //hori
			i++;
		}
		x += size;
		j++;
	}
}

int main()
{
	void *img_ptr;
	t_data img;
	t_params params;

	int i = 0;
	int j = 0;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, 500, 500, "cub3d");
	img.img = mlx_new_image(params.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while(i < MAP_ROWS )
	{
		j = 0;
		while(j < MAP_COLS)
		{
			if(grid[i][j] == 1)
			{
				minimap_borders(j, i, 10, &img);
				my_mlx_pixel_put(&img, j, i, 0x00FF0000); //hori
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(params.mlx, params.win, img.img, 10, 10);
/*
 	mlx_key_hook(params.win, key_hook, &params);
	mlx_hook(params.win, 4, 1L<<2, close, &params);
*/
	mlx_loop(params.mlx);
}

