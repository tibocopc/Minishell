/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:34:11 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/05 14:59:39 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **res, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
		free(res[i++]);
	free(res);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c == '\0')
	{
		if (*s == '\0')
			return (0);
		return (1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static int	taille_s(char const *s, char c, int index)
{
	int	count;

	count = 0;
	while (s[index] != '\0' && s[index] != c)
	{
		count++;
		index++;
	}
	return (count);
}

static int	fill_tab(char const *s, char c, int index, char **res)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[index])
	{
		res[i] = (char *)malloc(sizeof(char) * (taille_s(s, c, index) + 1));
		if (!res[i])
		{
			free_split(res, i);
			return (1);
		}
		j = 0;
		while (s[index] != c && s[index] != '\0')
			res[i][j++] = s[index++];
		res[i][j] = '\0';
		while (s[index] != '\0' && s[index] == c)
			index++;
		i++;
	}
	res[i] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**res;

	if (!s)
		return (0);
	res = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (0);
	if (count_words(s, c) == 0)
	{
		res[0] = 0;
		return (res);
	}
	index = 0;
	while (s[index] == c)
		index++;
	if (fill_tab(s, c, index, res))
		return (0);
	return (res);
}
