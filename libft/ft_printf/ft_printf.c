/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:16:19 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/12 11:44:03 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_convert_data(const char *format, int i, va_list *args)
{
	if (format[i + 1] == 'c')
		return (ft_printchar((char)va_arg(*args, int)));
	else if (format[i + 1] == 's')
		return (ft_printstr((char *)va_arg(*args, char *)));
	else if (format[i + 1] == 'i' || format[i + 1] == 'd')
		return (ft_printnbr(va_arg(*args, int)));
	else if (format[i + 1] == 'u')
		return (ft_printunbr(va_arg(*args, unsigned int)));
	else if (format[i + 1] == 'x' || format[i + 1] == 'X')
		return (ft_printhexa(va_arg(*args, int), format[i + 1]));
	else if (format[i + 1] == '%')
		return (ft_printchar('%'));
	else if (format[i + 1] == 'p')
		return (ft_printptr((unsigned long long int)va_arg(*args, void *)));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		while (format[i] != '%' && format[i] != '\0')
			count += ft_printchar(format[i++]);
		if (format[i] == '%')
		{
			count += ft_convert_data(format, i, &args);
			i += 2;
		}
	}
	va_end(args);
	return (count);
}
