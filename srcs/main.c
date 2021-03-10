/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:12:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/03/10 11:50:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Init all of our ressources and then start the game.
*/

void	init_cub(t_cub *cub, char *map)
{
	init_win(&cub->win);
	init_img(&cub->win.img);
	init_grid(cub);
	init_player(&cub->player);
	init_texture(cub);
	cub->ray_load = 0;
	cub->sprt_load = 0;
	cub->mlx_load = 0;
	cub->data.txtr_err = 0;
	load_cub(cub, map);
}

/*
** Free all of our ressources.
*/

int		end_cub(t_cub *cub)
{
	free_texture(cub);
	if (cub->sprt_load == 1)
		free_sprt(cub);
	if (cub->ray_load == 1)
		free(cub->rays);
	if (cub->data.rows)
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
		if (cub->data.txtr_err == 1 || cub->win.wid < 1)
		{
			if (cub->win.wid < 1)
				is_error("Map has no valid resolution");
			ft_lstclear(&list, &ft_free);
			end_cub(cub);
		}
		if (!grid_parsing(cub, list) || !load_texture(cub) || !load_sprt(cub) ||
				!check_missing(cub))
			end_cub(cub);
		printf("Cub3d is launching..\n");
		run_cub(cub);
	}
	else
	{
		ft_lstclear(&list, &ft_free);
		end_cub(cub);
	}
}

/*
** If save arg true, then just copy the 1st image. Otherwise, loop the render.
*/

void	run_cub(t_cub *cub)
{
	load_img(&cub->win);
	if (cub->save)
	{
		render(cub);
		save_bmp(cub);
		end_cub(cub);
	}
	load_win(&cub->win);
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_loop_hook(cub->win.mlx_p, render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	mlx_loop(cub->win.mlx_p);
}

int		main(int ac, char **av)
{
	t_cub cub;

	if (ac == 3 && !ft_strcmp(av[2], "--save"))
	{
		if (cub_ext(av[1]))
		{
			cub.save = 1;
			init_cub(&cub, av[1]);
		}
		return (0);
	}
	else if (ac == 2)
	{
		if (cub_ext(av[1]))
		{
			cub.save = 0;
			init_cub(&cub, av[1]);
		}
		return (0);
	}
	else
		return (is_error("Wrong numbers of arguments"));
	return (0);
}
