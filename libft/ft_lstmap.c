/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:52:09 by bahaas            #+#    #+#             */
/*   Updated: 2020/11/18 10:39:54 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *second_lst;
	t_list *new;

	second_lst = NULL;
	while (lst)
	{
		if ((new = ft_lstnew((*f)(lst->content))) == NULL)
		{
			ft_lstclear(&second_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&second_lst, new);
		lst = lst->next;
	}
	return (second_lst);
}
