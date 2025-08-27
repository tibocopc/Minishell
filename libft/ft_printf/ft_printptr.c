/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:44:25 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/12 12:00:05 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ptr_len(unsigned long long int nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

static int	ft_printptr_hexa(const unsigned long long int n)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n <= 15)
		ft_printchar(tab[n]);
	if (n > 15)
	{
		ft_printptr_hexa(n / 16);
		ft_printptr_hexa(n % 16);
	}
	return (ptr_len(n));
}

int	ft_printptr(unsigned long long int ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += write(1, "(nil)", 5);
	else
	{
		len += write(1, "0x", 2);
		len += ft_printptr_hexa(ptr);
	}
	return (len);
}
