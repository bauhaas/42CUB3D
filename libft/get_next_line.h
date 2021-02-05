/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 23:03:02 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/05 02:51:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

# include <unistd.h>
# include <stdlib.h>

int			get_next_line(const int fd, char **line);
size_t		ft_strlen(const char *str);
char		*ft_strnew(size_t size);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
