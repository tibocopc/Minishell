/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:43:49 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 19:31:21 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_allpath(char **allpath)
{
	int	i;

	i = -1;
	while (allpath[++i])
		free(allpath[i]);
	free(allpath);
}

static char	*check_absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*path_env;
	char	**allpath;
	char	*resolved;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);
	allpath = ft_split(path_env, ':');
	if (!allpath)
		return (NULL);
	resolved = search_path_in_dirs(cmd, allpath);
	free_allpath(allpath);
	return (resolved);
}

char	*search_path_in_dirs(char *cmd, char **allpath)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = 0;
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (path_part)
		{
			exec = ft_strjoin(path_part, cmd);
			free(path_part);
			if (exec)
			{
				if (access(exec, F_OK | X_OK) == 0)
					return (exec);
				free(exec);
			}
		}
		i++;
	}
	return (NULL);
}
