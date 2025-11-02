/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:31:35 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 19:21:24 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_env_var(char ***env, const char *key, const char *value)
{
	size_t	len;
	char	*new_var;
	char	**new_env;
	int		i;
	int		j;

	len = ft_strlen(key);
	new_var = join_key_value(key, value);
	if (!new_var)
		return (perror("malloc"), 1);
	i = -1;
	while ((*env)[++i])
		if (ft_strncmp((*env)[i], key, len) == 0 && (*env)[i][len] == '=')
			return (free((*env)[i]), (*env)[i] = new_var, 0);
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (perror("malloc"), free(new_var), 1);
	j = -1;
	while (++j < i)
		new_env[j] = (*env)[j];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (free(*env), *env = new_env, 0);
}

int	ft_cd(char **args, char ***env)
{
	char		*oldpwd;
	char		*newpwd;
	const char	*path;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 1);
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), free(oldpwd), 1);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
		return (write(2, "cd: ", 4), perror(path), free(oldpwd), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("getcwd"), free(oldpwd), 1);
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	return (free(oldpwd), free(newpwd), 0);
}
