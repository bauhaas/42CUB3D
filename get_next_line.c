/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:07:08 by bahaas            #+#    #+#             */
/*   Updated: 2020/11/26 12:38:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*store_leftover(char *tmp_buf)
{
	int		i;
	char	*leftover;

	i = 0;
	if (!tmp_buf)
		return (NULL);
	while (tmp_buf[i] && tmp_buf[i] != '\n')
		i++;
	leftover = ft_substr(tmp_buf, i + 1, ft_strlen(tmp_buf) - i);
	return (leftover);
}

char	*grep_found_line(char *tmp_buf)
{
	char	*current_line;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (tmp_buf[i] && tmp_buf[i] != '\n')
		i++;
	current_line = malloc(sizeof(char) * i + 1);
	if (!current_line)
		return (NULL);
	while (start < i)
	{
		current_line[start] = tmp_buf[start];
		start++;
	}
	current_line[i] = '\0';
	return (current_line);
}

int		ln_and_lftvr(char *tmp_buf, char **leftover, int read_size, char **line)
{
	if (read_size == 0 && (tmp_buf == NULL || tmp_buf[0] == '\0'))
	{
		free(tmp_buf);
		if (leftover == NULL)
			free(*leftover);
		*line = ft_strdup("");
		return (0);
	}
	*line = grep_found_line(tmp_buf);
	if (!check_line(tmp_buf))
	{
		free(*leftover);
		*leftover = NULL;
		free(tmp_buf);
		return (0);
	}
	free(*leftover);
	*leftover = store_leftover(tmp_buf);
	free(tmp_buf);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*leftover;
	int				read_size;
	char			buf[BUFFER_SIZE + 1];
	char			*tmp_buf;

	tmp_buf = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (leftover)
		tmp_buf = ft_strdup(leftover);
	while (!check_line(tmp_buf) && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		tmp_buf = free_then_join(tmp_buf, buf, ft_strlen(tmp_buf));
		if (read_size < 0)
		{
			free(tmp_buf);
			free(leftover);
			return (-1);
		}
	}
	return (ln_and_lftvr(tmp_buf, &leftover, read_size, line));
}
