/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:46 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 16:40:52 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*alloc_fail(t_list *map, void *content, void (*del)(void *))
{
	if (content)
		(*del)(content);
	if (map)
		ft_lstclear(&map, (*del));
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*temp;
	void	*content;

	if (!lst)
		return (NULL);
	content = (*f)(lst->content);
	map = ft_lstnew(content);
	if (!map)
		return (alloc_fail(map, content, (*del)));
	while (lst->next)
	{
		lst = lst->next;
		content = (*f)(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
			return (alloc_fail(map, content, (*del)));
		ft_lstadd_back(&map, temp);
	}
	return (map);
}
