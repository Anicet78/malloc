/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_dlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:45:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/28 13:55:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_strstr_dlst(t_dlist *lst, char *str)
{
	if (!lst || !lst->content)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, str) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
