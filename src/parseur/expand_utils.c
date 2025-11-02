/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:30:00 by xx                #+#    #+#             */
/*   Updated: 2025/11/01 16:55:46 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char **env, char *var_name)
{
	int		i;
	int		len;
	char	*eq;

	if (!env || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (eq && (eq - env[i]) == len && ft_strncmp(env[i], var_name,
				len) == 0)
			return (eq + 1);
		i++;
	}
	return (NULL);
}

char	*expand_status(char *expanded, int last_status)
{
	char	*tmp;
	char	*status;

	status = ft_itoa(last_status);
	tmp = ft_strjoin(expanded, status);
	free(expanded);
	free(status);
	return (tmp);
}

char	*expand_variable(char *expanded, char *dollar, char **env)
{
	char	*var_name;
	char	*val;
	char	*tmp;
	int		j;

	j = 1;
	while (ft_isalnum(dollar[j]) || dollar[j] == '_')
		j++;
	var_name = ft_substr(dollar + 1, 0, j - 1);
	val = get_env_value(env, var_name);
	free(var_name);
	if (!val)
		val = "";
	tmp = ft_strjoin(expanded, val);
	free(expanded);
	return (tmp);
}
