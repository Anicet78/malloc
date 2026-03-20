/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:00:35 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 12:46:08 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_null(t_printf *ft_print)
{
	if (ft_print->flags & PRECISION && ft_print->precision < 6)
		return (0);
	if (write_to_buff(ft_print, "(null)", 6) == -1)
		return (-1);
	return (6);
}

int	write_sharp(t_printf *ft_print, char *base)
{
	if (ft_strcmp(base, BASE_16L) == 0)
		return (write_to_buff(ft_print, "0x", 2));
	else if (ft_strcmp(base, BASE_16U) == 0)
		return (write_to_buff(ft_print, "0X", 2));
	return (0);
}

int	write_sign(t_printf *ft_print, bool is_neg)
{
	if (is_neg)
		return (write_to_buff(ft_print, "-", 1));
	if (ft_print->flags & SHOW_SIGN)
		return (write_to_buff(ft_print, "+", 1));
	if (ft_print->flags & SPACE_POSITIVE)
		return (write_to_buff(ft_print, " ", 1));
	return (0);
}

int	write_padding(t_printf *ft_print, int padding, int c)
{
	int	i;

	i = 0;
	while (i < padding)
	{
		if (write_to_buff(ft_print, (char *)&c, 1) == -1)
			return (-1);
		i++;
	}
	if (padding < 0)
		padding = 0;
	return (padding);
}

int	apply_numeric_flag(t_printf *ft_print, int len, char *base, bool is_neg)
{
	if (!(ft_print->flags & PAD_ZEROS) && !(ft_print->flags & LEFT_JUSTIFY))
	{
		if (write_padding(ft_print, ft_print->padding - len, ' ') == -1)
			return (-1);
	}
	if (write_sign(ft_print, is_neg) == -1)
		return (-1);
	if (ft_print->flags & ALTERNATIVE_FORM && write_sharp(ft_print, base) == -1)
		return (-1);
	if (ft_print->flags & PAD_ZEROS)
	{
		if (write_padding(ft_print, ft_print->padding - len, '0') == -1)
			return (-1);
	}
	if (ft_print->flags & PRECISION && ft_print->precision > 0)
	{
		if (write_padding(ft_print, ft_print->precision - 1, '0') == -1)
			return (-1);
	}
	return (0);
}
