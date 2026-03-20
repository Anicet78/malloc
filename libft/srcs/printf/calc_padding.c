/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_padding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:32:38 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 11:45:18 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_str_size(t_printf *ft_print, char *str)
{
	int		size;
	size_t	len;

	size = 0;
	len = ft_strlen(str);
	if (str && ft_print->flags & PRECISION && ft_print->precision < (int)len)
		size = ft_print->precision;
	else if (str)
		size = ft_strlen(str);
	else if (!str && ft_print->flags & PRECISION && ft_print->precision < 6)
		size = 0;
	else if (!str)
		size = 6;
	return (ft_print->padding - size);
}

int	calc_uint_size(t_printf *ft_print, unsigned int nb, int base_len)
{
	int				size;
	int				precision;
	unsigned int	divisor;

	size = 1;
	divisor = 1;
	while (nb / divisor >= (unsigned int)base_len)
	{
		size++;
		divisor *= base_len;
	}
	precision = ft_print->precision;
	if (precision != 0)
		ft_print->precision++;
	if (nb == 0 && ft_print->flags & PRECISION && precision == 0)
		size--;
	ft_print->precision -= size;
	if (size < precision)
		size = precision;
	if (nb != 0 && ft_print->flags & ALTERNATIVE_FORM)
		size += 2;
	return (size);
}

int	calc_int_size(t_printf *ft_print, int n, int base_len)
{
	int				size;
	int				precision;
	unsigned int	nb;
	unsigned int	divisor;

	size = 1;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= (unsigned int)base_len && size++)
		divisor *= base_len;
	precision = ft_print->precision;
	if (precision != 0)
		ft_print->precision++;
	if (n == 0 && ft_print->flags & PRECISION && precision == 0)
		size--;
	ft_print->precision -= size;
	if (size < precision)
		size = precision;
	if (n < 0 && (ft_print->flags & SPACE_POSITIVE
			|| ft_print->flags & SHOW_SIGN))
		size++;
	return (size);
}

int	calc_llong_size(t_printf *ft_print, unsigned long long ptr)
{
	int		size;
	size_t	divisor;

	ft_print->precision = 0;
	if (!ptr)
	{
		ft_print->flags &= ~ALTERNATIVE_FORM;
		return (5);
	}
	divisor = 1;
	size = 1;
	while (ptr / divisor >= 16)
	{
		size++;
		divisor *= 16;
	}
	size += 2;
	return (size);
}
