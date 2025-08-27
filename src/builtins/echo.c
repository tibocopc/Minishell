/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:52:09 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/19 17:05:15 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	else
		return (0);
	if (arg[i] == 'n')
	{
		while (arg[i] == 'n')
			i++;
	}
	else
		return (0);
	if (!arg[i])
		return (1);
	return (0);
}

void	ft_echo(char **tab)
{
	int i;
	int nl;

	nl = 0;
	i = 1;
	while (is_flag(tab[i]))
	{
		i++;
		nl = 1;
	}
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl == 1)
		return ;
	ft_putchar_fd('\n', 1);
	return ;
}