/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:30:56 by agruet            #+#    #+#             */
/*   Updated: 2025/04/10 17:38:36 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flush_printf(t_printf *ft_print)
{
	if (ft_print->buff_pos <= 0)
		return (0);
	if (write(ft_print->fd, ft_print->buff, ft_print->buff_pos)
		< (long)ft_print->buff_pos)
	{
		ft_print->len = -1;
		return (-1);
	}
	ft_memset(ft_print->buff, 0, ft_print->buff_size);
	ft_print->buff_pos = 0;
	ft_print->len += ft_print->buff_pos;
	return (0);
}

static int	fill_write(t_printf *ft_print, char *to_write)
{
	if (flush_printf(ft_print))
		return (-1);
	ft_memmove(ft_print->buff, to_write, ft_print->buff_size);
	if (write(ft_print->fd, ft_print->buff, ft_print->buff_size)
		< (long)ft_print->buff_size)
	{
		ft_print->len = -1;
		return (-1);
	}
	ft_print->buff_pos = 0;
	ft_print->len += ft_print->buff_size;
	return (0);
}

int	write_to_buff(t_printf *ft_print, char *to_write, size_t size)
{
	while (size >= ft_print->buff_size)
	{
		if (fill_write(ft_print, to_write) == -1)
			return (-1);
		to_write += ft_print->buff_size;
		size -= ft_print->buff_size;
	}
	if (ft_print->buff_pos + size >= ft_print->buff_size)
	{
		if (flush_printf(ft_print) == -1)
			return (-1);
	}
	ft_memmove(ft_print->buff + ft_print->buff_pos, to_write, size);
	ft_print->buff_pos += size;
	ft_print->len += size;
	return (0);
}
