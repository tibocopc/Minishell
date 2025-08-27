/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:40:48 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/01 14:25:37 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		lent;
	char		*res;

	i = 0;
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (start + len > ft_strlen(s))
		lent = ft_strlen(s) - start;
	else
		lent = len;
	res = malloc(sizeof(char) * lent + 1);
	if (!res)
		return (0);
	while (lent > 0)
	{
		res[i] = s[start];
		i++;
		start++;
		lent--;
	}
	res[i] = '\0';
	return (res);
}
