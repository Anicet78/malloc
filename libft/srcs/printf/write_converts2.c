/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:14:07 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 13:19:36 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_ulong(t_printf *ft_print, unsigned long nb, char *base, int len)
{
	unsigned long	divisor;
	int				calc_size;

	calc_size = calc_ulong_size(ft_print, nb, len);
	if (nb == 0)
		ft_print->flags &= ~ALTERNATIVE_FORM;
	if (apply_numeric_flag(ft_print, calc_size, base, false) == -1)
		return ;
	divisor = 1;
	while (nb / divisor >= (unsigned long)len)
		divisor *= len;
	while (divisor > 0)
	{
		if (ft_print->flags & PRECISION && ft_print->precision <= 0 && nb == 0)
			break ;
		if (write_to_buff(ft_print, &base[nb / divisor % len], 1) == -1)
			return ;
		divisor /= len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}

void	write_long(t_printf *ft_print, long n, char *base, int base_len)
{
	unsigned long	nb;
	unsigned long	divisor;
	int				calc_size;

	calc_size = calc_long_size(ft_print, n, base_len);
	if (apply_numeric_flag(ft_print, calc_size, base, n < 0) == -1)
		return ;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= (unsigned long)base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		if (ft_print->flags & PRECISION && ft_print->precision <= 0 && nb == 0)
			break ;
		if (write_to_buff(ft_print, &base[nb / divisor % base_len], 1) == -1)
			return ;
		divisor /= base_len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}

static void	sanitize_double(t_printf *ft_print, int *precision, bool *dot)
{
	if (ft_print->flags & PRECISION)
	{
		*precision = ft_print->precision;
		ft_print->flags &= ~PRECISION;
	}
	else
		*precision = 6;
	*dot = false;
	if (ft_print->flags & ALTERNATIVE_FORM)
	{
		ft_print->flags &= ~ALTERNATIVE_FORM;
		*dot = true;
	}
}

static size_t	write_double_ulong(t_printf *ft_print, unsigned long n)
{
	unsigned long	divisor;
	int				size;

	size = 0;
	divisor = 1;
	while (n / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		if (write_to_buff(ft_print, &BASE_10[n / divisor % 10], 1) == -1)
			return (-1);
		divisor /= 10;
		size++;
	}
	return (size);
}

void	write_double(t_printf *ft_print, double n)
{
	int		precision;
	bool	print_dot;
	int		calc_size;

	sanitize_double(ft_print, &precision, &print_dot);
	calc_size = calc_double_size(ft_print, n, precision, print_dot);
	if (apply_numeric_flag(ft_print, calc_size, BASE_10, n < 0) == -1)
		return ;
	if (n < 0)
		n = -n;
	write_double_ulong(ft_print, (unsigned long)n);
	if (precision > 0 || print_dot == true)
		write_to_buff(ft_print, ".", 1);
	while (precision-- > 0)
	{
		n -= (long)n;
		n *= 10;
		write_double_ulong(ft_print, (unsigned long)n);
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}
