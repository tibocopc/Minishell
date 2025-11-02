/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 16:55:48 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum_or_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_strlen_while(char *s, int (*f)(char))
{
	int	i;

	i = 0;
	while (s[i] && f(s[i]))
		i++;
	return (i);
}

void	free_both(char *a, char *b)
{
	free(a);
	free(b);
}
