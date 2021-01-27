/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:58:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/27 17:27:01 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= WIN_WID  && y >= 0 && y <= WIN_HEI)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	render_minimap_square(int x, int y, int size, t_cub3d *cub3d)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&cub3d->img, x + j, y + i, GRAY);
			j++;
		}
		i++;
	}
}

void	render_minimap_square_back(int x, int y, int size, t_cub3d *cub3d)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&cub3d->img, x + j, y + i, BLUE);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_cub3d *cub3d)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_ROWS )
	{
		j = 0;
		while (j < MAP_COLS)
		{
			if (cub3d->grid[i][j] == '1')
			{
				//render_minimap_square((j * TILE_SIZE), (i * TILE_SIZE), TILE_SIZE, cub3d);
				//render_minimap_square(MINIMAP_SCALE * (j * TILE_SIZE) + j, MINIMAP_SCALE * (i * TILE_SIZE) + i, MINIMAP_SCALE * TILE_SIZE, cub3d);
				render_minimap_square(MINIMAP_SCALE * (j * TILE_SIZE), MINIMAP_SCALE * (i * TILE_SIZE), MINIMAP_SCALE * TILE_SIZE, cub3d);
			}
		/*	
			if (cub3d->grid[i][j] == '0')
			{
				//render_minimap_square((j * TILE_SIZE), (i * TILE_SIZE), TILE_SIZE, cub3d);
				render_minimap_square_back(MINIMAP_SCALE * (j * TILE_SIZE) + j, MINIMAP_SCALE * (i * TILE_SIZE) + i, MINIMAP_SCALE * TILE_SIZE, cub3d);
			}*/
			j++;
		}
		i++;
	}
}

/*
**	Bresenham line algorithm
*/ 

//void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
//{
/*
	float e2;
	float dx =  abs(line->end.x -line->start.x);
	float sx = line->start.x < line->end.x ? 1 : -1;
	float dy = -abs(line->end.y - line->start.y);
	float sy = line->start.y < line->end.y ? 1 : -1;
	float err = dx+dy;
	while (1) 
	{
		my_mlx_pixel_put(&cub3d->img, line->start.x, line->start.y, WHITE);
		if (line->start.x == line->end.x && line->start.y == line->end.y)
		{
			printf("test\n");
			break ;
		}
		e2 = 2*err;
		if (e2 >= dy)
		{
			err += dy;
			line->start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			line->start.y += sy;
		}
	}	
*/
/*
	float t;
	float x; 
	float y;

	t = 0;
	while(t < 1)
	{
	x = line->start.x + (line->end.x - line->start.x)*t - 6;
	y = line->start.y + (line->end.y - line->start.y)*t - 6;
	my_mlx_pixel_put(&cub3d->img, x + cub3d->player.radius, y + cub3d->player.radius, color);
	t += 0.001;
	}
*/

/*
 * DDA Line Algorithm
*/

void	render_view_line(t_line *line, t_cub3d *cub3d, int color)
{
	int delta_x = line->end.x - line->start.x;
	int delta_y = line->end.y - line->start.y;

	int longest_side = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);
	float x_inc = delta_x / (float)longest_side;
	float y_inc = delta_y / (float)longest_side;

	float curr_x = line->start.x;
	float curr_y = line->start.y;
	for(int i = 0; i < longest_side; i++)
	{
		my_mlx_pixel_put(&cub3d->img, round(curr_x), round(curr_y), color);
		curr_x += x_inc;
		curr_y += y_inc;
	}
}

void	render_player(t_cub3d *cub3d)
{
	t_line line;

	line.start.x = MINIMAP_SCALE * cub3d->player.pos.x;
	line.start.y = MINIMAP_SCALE * cub3d->player.pos.y;
	//line.start.x = cub3d->player.pos.x;
	//line.start.y = cub3d->player.pos.y;
	line.end.y = line.start.y + sin(cub3d->player.rot_ang) * (TILE_SIZE / 2);
	line.end.x = line.start.x + cos(cub3d->player.rot_ang) * (TILE_SIZE / 2);

	//render_minimap_square(line.start.x - 3, line.start.y - 3, cub3d->player.radius, cub3d);
	render_view_line(&line, cub3d, WHITE);
}
