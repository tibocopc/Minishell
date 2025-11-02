/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:39:12 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 17:43:31 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(char ***env, const char *key)
{
	size_t	len;
	int		count;
	char	**new_env;
	int		i;

	if (!env || !*env || !key)
		return ;
	len = ft_strlen(key);
	i = find_env_index(*env, key, len);
	if (i == -1)
		return ;
	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (perror("malloc"), (void)0);
	copy_env_without_index(new_env, *env, i);
	new_env[count - 1] = NULL;
	free((*env)[i]);
	free(*env);
	*env = new_env;
}

static int	process_unset_arg(char *arg, char ***env)
{
	if (!is_valid_identifier(arg))
	{
		write(2, "unset: `", 8);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	remove_env_var(env, arg);
	return (0);
}

int	ft_unset(char **args, char ***env)
{
	int	status;
	int	i;

	status = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (process_unset_arg(args[i], env))
			status = 1;
		i++;
	}
	return (status);
}
