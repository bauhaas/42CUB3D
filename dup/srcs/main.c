/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:45:14 by clorin            #+#    #+#             */
/*   Updated: 2021/01/12 16:37:36 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		load_file(t_game *game, char *file_name)
{
	int			fd;
	char		*line;
	int			ret;
	t_list		*list;
	int			nb_oct;

	ret = TRUE;
	list = NULL;
	nb_oct = 1;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		msg_err(FAIL_OPEN, file_name);
		return (FALSE);
	}
	while (nb_oct > 0)
	{
		nb_oct = get_next_line(fd, &line);
		ret = ret && parse_line(line, game, &list);
		free(line);
	}
	close(fd);
	game->map.name = ft_strdup(file_name);
	return (valid_game(game, list, ret));
}

static void		init(char *file_name, int save)
{
	t_game		game;

	init_game(&game, save);
	if (load_file(&game, file_name))
		run_game(&game);
	game_close(&game);
}

static int		is_valid_file(char *file_name)
{
	int		i;

	i = 0;
	while (file_name[i] != '\0')
		i++;
	i -= 4;
	if (i > 0)
		return (ft_strequ(&file_name[i], ".cub"));
	else
		return (FALSE);
}

int				main(int argc, char **argv)
{
	if (argc == 3 && is_valid_file(argv[1]) && ft_strequ(argv[2], "--save"))
	{
		init(argv[1], TRUE);
	}
	else if (argc == 2)
	{
		if (is_valid_file(argv[1]))
			init(argv[1], FALSE);
		else
			msg_err(BAD_MAP_FILE, "");
	}
	else
		msg_err(BAD_ARG, "");
	return (0);
}
