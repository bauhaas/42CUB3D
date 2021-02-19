/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:12:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/19 04:07:02 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Init all of our ressources and then start the game.
*/

void	init_cub(t_cub *cub, char *map)
{
	printf("test\n");
	init_win(&cub->win);
	init_img(&cub->img);
	init_grid(cub);
	init_player(&cub->player);
	init_texture(cub);
	load_cub(cub, map);
}

/*
** Free all of our ressources.
*/

int		end_cub(t_cub *cub)
{
	free(cub->rays);
	free_texture(cub);
	free_sprt(cub);
	free_grid(cub);
	if (cub->win.img.img)
		free_img(cub);
	free_win(cub);
	exit(0);
}

/*
** If we have a valid map, load the game.
*/

void	load_cub(t_cub *cub, char *map)
{
	t_list	*list;

	list = NULL;
	if (parsing(cub, map, &list))
	{
		if (!check_missing(cub) || !grid_parsing(cub, list) ||
		!load_texture(cub) || !load_sprt(cub))
			end_cub(cub);
		printf("Cub3d is launching..\n");
		run_cub(cub);
	}
}

/*
** If save arg true, then just copy the 1st image. Otherwise, loop the render.
*/

void	run_cub(t_cub *cub)
{
	load_win(&cub->win);
	load_img(&cub->win);
	//if (cub->save)
	//{
	//	render(cub);
	//	save_bmp(cub);
	//	end_cub(cub);
	//}
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->win.win_p, 9, 1L << 21, &render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	render(cub);
	mlx_loop(cub->win.mlx_p);
}

int		main(int ac, char **av)
{
	t_cub cub;

	if (ac == 3 && cub_ext(av[1]) && !strcmp(av[2], "--save"))
		init_cub(&cub, av[1]);
	else if (ac == 2 && cub_ext(av[1]))
		init_cub(&cub, av[1]);
	else
		return (is_error("Wrong numbers of arguments"));
	return (0);
}
