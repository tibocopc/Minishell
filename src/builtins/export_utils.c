/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:58:17 by xx                #+#    #+#             */
/*   Updated: 2025/11/01 19:31:20 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_new_var(char ***env, char *var)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (perror("malloc"), 1);
	i = 0;
	while ((*env) && (*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	if (!new_env[count])
		return (perror("malloc"), 1);
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

static char	*create_var_string(char *key, char *value)
{
	char	*new_var;

	if (!value)
	{
		new_var = ft_strdup(key);
		if (!new_var)
			perror("malloc");
	}
	else
	{
		new_var = join_key_value(key, value);
		if (!new_var)
			perror("malloc");
	}
	return (new_var);
}

int	update_or_add_env(char ***env, char *key, char *value)
{
	int		idx;
	char	*new_var;

	idx = find_var_index(*env, key);
	new_var = create_var_string(key, value);
	if (!new_var)
		return (1);
	if (idx >= 0)
	{
		free((*env)[idx]);
		(*env)[idx] = new_var;
	}
	else
	{
		add_new_var(env, new_var);
		free(new_var);
	}
	return (0);
}
