/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:34:53 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 17:32:00 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_export_error(char *arg, char *eq)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	if (eq)
	{
		ft_putstr_fd("=", 2);
		ft_putstr_fd(eq + 1, 2);
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	export_with_value(char **args, char ***env, int i)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(args[i], '=');
	*eq = '\0';
	key = args[i];
	if (!is_valid_identifier(key))
	{
		handle_export_error(args[i], eq);
		*eq = '=';
		return (1);
	}
	value = eq + 1;
	update_or_add_env(env, key, value);
	*eq = '=';
	return (0);
}

static int	export_without_value(char **args, char ***env, int i)
{
	char	*key;

	key = args[i];
	if (!is_valid_identifier(key))
	{
		handle_export_error(key, NULL);
		return (1);
	}
	update_or_add_env(env, key, NULL);
	return (0);
}

int	ft_export(char **args, char ***env)
{
	int	i;
	int	ret;

	if (!args[1])
		return (print_export(*env), 0);
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			ret |= export_with_value(args, env, i);
		else
			ret |= export_without_value(args, env, i);
		i++;
	}
	return (ret);
}
