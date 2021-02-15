/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:12:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/15 03:29:17 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

void	init_cub(t_cub *cub)
{
	init_win(&cub->win);
	init_img(&cub->img);
	init_grid(cub);
	init_player(&cub->player);
	init_texture(cub);
}

int		end_cub(t_cub *cub)
{
	free(cub->rays);
	free_texture(cub);
	free_sprite(cub);
	free_grid(cub);
	if (cub->win.img.img)
		free_img(cub);
	free_win(cub);
	exit(0);
}

void	run_cub(t_cub *cub)
{
	load_win(&cub->win);
	load_img(&cub->win);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_hook(cub->win.win_p, 9, 1L << 21, &render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	render(cub);
	mlx_loop(cub->win.mlx_p);
}

int		main(int ac, char **av)
{
	t_cub cub;

	if (ac == 3 && !strcmp(av[2], "--save"))
		return (0);
	else if (ac == 2)
	{
		if (cub_ext(av[1]))
		{
			init_cub(&cub);
			if (parsing(&cub, av[1]))
			{
				cub.data.dist_proj_plane = (cub.win.wid / 2) /
					(tan(FOV / 2));
					cub.rays = malloc(sizeof(t_ray) * cub.win.wid);
					if(!cub.rays)
						return (is_error("MAlloc space rays"));
				printf("Cub3d is launching..\n");
				run_cub(&cub);
				end_cub(&cub);
			}
		}
	}
	else
		return (is_error("Wrong numbers of arguments"));
	return (0);
}
