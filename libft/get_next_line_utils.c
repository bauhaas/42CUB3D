/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:24:58 by bahaas            #+#    #+#             */
/*   Updated: 2020/11/26 00:04:14 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_src;
	unsigned char	*tmp_dest;

	i = -1;
	if (!dest && !src)
		return (NULL);
	tmp_src = (unsigned char *)src;
	tmp_dest = (unsigned char *)dest;
	if (tmp_src > tmp_dest)
	{
		while (++i < n)
			tmp_dest[i] = tmp_src[i];
	}
	else
	{
		while (n > 0)
		{
			tmp_dest[n - 1] = tmp_src[n - 1];
			n--;
		}
	}
	return (tmp_dest);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (NULL);
	while (i < ft_strlen(s))
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
** Only twist with my ft_substr from my libft project is to use :
** ft_strdup("") in case where start > ft_strlen(s) to save space and
** not use ft_calloc
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
** Free the actual tmp_buf to avoid leaks by multiplying my call to this
** fucntion during my reading loop. Create string to store the memory of
** buf and tmp_buf. Store 1st mem of tmp_buf via memmove and then store
** at the end of tmp_buf in str, the buf
*/

char	*free_then_join(char *s1, char *s2, int size_s1)
{
	char	*str;
	int		size_s2;

	size_s2 = ft_strlen(s2);
	if (!s1)
		return (ft_strdup(s2));
	if (!(str = malloc(sizeof(char) * size_s2 + size_s1 + 1)))
		return (NULL);
	ft_memmove(str, s1, size_s1);
	ft_memmove(&str[size_s1], s2, size_s2);
	str[size_s1 + size_s2] = '\0';
	free(s1);
	return (str);
}
