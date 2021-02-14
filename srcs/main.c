/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:12:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/14 21:59:19 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		cub_ext(char *map_file)
{
	int i;

	i = 0;
	while (map_file[i])
		i++;
	i -= 4;
	if (!strcmp(&map_file[i], ".cub"))
		return (1);
	return (is_error("Map argument is not ending with .cub"));
}

void	init_cub3d(t_cub3d *cub3d, char *file)
{
	init_win(&cub3d->win);
	init_img(&cub3d->img, &cub3d->win);
	init_grid(cub3d);
	init_player(&cub3d->player);
	init_texture(cub3d);
}

int		end_cub3d(t_cub3d *cub3d)
{
	free_texture(cub3d);
	free_sprite(cub3d);
	free_grid(cub3d);
	if (cub3d->win.img.img)
		free_img(cub3d);
	free_win(cub3d);
	exit(0);
}

void	run_cub3d(t_cub3d *cub3d)
{
	load_win(&cub3d->win);
	load_img(&cub3d->win);
	mlx_hook(cub3d->win.win_p, 2, 1L << 0, key_pressed, cub3d);
	mlx_hook(cub3d->win.win_p, 3, 1L << 1, key_released, &cub3d->player);
	mlx_hook(cub3d->win.win_p, 33, 1L << 17, &end_cub3d, cub3d);
	render(cub3d);
	mlx_loop(cub3d->win.mlx_p);
}

int		main(int ac, char **av)
{
	t_cub3d cub3d;

	if (ac == 3 && av[2] == "--save")
		return (0);
	else if (ac == 2)
	{
		if (cub_ext(av[1]))
		{
			init_cub3d(&cub3d, av[1]);
			if (parsing(&cub3d, av[1]))
			{
				cub3d.data.dist_proj_plane = (cub3d.win.wid / 2) /
					(tan(FOV / 2));
				printf("Cub3d is launching..\n");
				run_cub3d(&cub3d);
				end_cub3d(&cub3d);
			}
		}
	}
	else
		return (is_error("Wrong numbers of arguments"));
	return (0);
}
