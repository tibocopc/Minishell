/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:58:17 by xx                #+#    #+#             */
/*   Updated: 2025/11/01 17:32:00 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_var_index(char **env, const char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*join_key_value(const char *key, const char *value)
{
	size_t	klen;
	size_t	vlen;
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	klen = ft_strlen(key);
	vlen = ft_strlen(value);
	res = malloc(klen + vlen + 2);
	if (!res)
		return (NULL);
	while (i < klen)
	{
		res[i] = key[i];
		i++;
	}
	res[i++] = '=';
	j = 0;
	while (j < vlen)
	{
		res[i + j] = value[j];
		j++;
	}
	return (res[i + j] = '\0', res);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		write(1, "declare -x ", 11);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
