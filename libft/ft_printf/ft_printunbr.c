/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:13:13 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/12 11:40:23 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_size_unbr(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
		nb = 2147483647 - nb;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_printunbr(const unsigned int nb)
{
	if (nb == 0)
		return (write(1, "0", 1));
	if (nb >= 0 && nb <= 9)
		ft_printchar(nb + '0');
	else
	{
		ft_printunbr(nb / 10);
		ft_printunbr(nb % 10);
	}
	return (ft_size_unbr(nb));
}
