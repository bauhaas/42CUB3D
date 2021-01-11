/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:12:50 by bahaas            #+#    #+#             */
/*   Updated: 2021/01/05 17:52:10 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define ERROR_MSG "Error\n"
# define ERROR_CUB ".cub file is missing in args\n"
# define ERROR_ARG "too many args are used\n"
# define ERROR_SVE "only accepts --save as 3rd arg\n"
typedef struct	s_struct
{
	int resolution[2];
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	char *sp_path;

	int floor[3];
	int ceiling[3];
}				t_struct;

#endif
