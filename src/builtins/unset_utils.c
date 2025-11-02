/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:30:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 17:44:18 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_env_index(char **env, const char *key, size_t len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	copy_env_without_index(char **new_env, char **old_env, int skip)
{
	int	j;

	j = 0;
	while (old_env[j])
	{
		if (j < skip)
			new_env[j] = old_env[j];
		else if (old_env[j + 1])
			new_env[j] = old_env[j + 1];
		else
			break ;
		j++;
	}
}
