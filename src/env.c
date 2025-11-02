/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:00:21 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 17:05:08 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_minimal_env(void)
{
	char	**env;
	char	cwd[1024];

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)))
		env[0] = ft_strjoin("PWD=", cwd);
	else
		env[0] = ft_strdup("PWD=/");
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

char	**copy_env(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp && envp[count])
		count++;
	if (count == 0)
		return (create_minimal_env());
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
