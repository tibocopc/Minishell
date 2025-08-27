/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:44:48 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/07 17:51:28 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_printhexa(const unsigned int n, char c)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n <= 15)
	{
		if (c == 'X' && n > 9)
			ft_printchar(tab[n] - 32);
		else
			ft_printchar(tab[n]);
	}
	if (n > 15)
	{
		ft_printhexa(n / 16, c);
		ft_printhexa(n % 16, c);
	}
	return (hex_len(n));
}
