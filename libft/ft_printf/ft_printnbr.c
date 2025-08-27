/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:47:55 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/12 11:37:12 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_size_nbr(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_printnbr(int nb)
{
	long long	n;

	n = nb;
	if (n < 0)
	{
		ft_printchar('-');
		n = -n;
	}
	if (n >= 0 && n <= 9)
		ft_printchar(n + '0');
	else
	{
		ft_printnbr(n / 10);
		ft_printnbr(n % 10);
	}
	return (ft_size_nbr(nb));
}
