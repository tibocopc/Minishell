/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:47:15 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 19:21:23 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	cleanup_and_exit(char ***env, char **args, int code)
{
	int	i;

	free_env(*env);
	if (args)
	{
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	exit(code);
}

int	ft_exit(char **args, int is_child, char ***env)
{
	int	code;

	code = 0;
	if (!is_child)
		printf("exit\n");
	if (!args[1])
		cleanup_and_exit(env, args, 0);
	if (!is_numeric(args[1]))
	{
		write(2, "exit: ", 6);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		cleanup_and_exit(env, args, 255);
	}
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	code = ft_atoi(args[1]);
	code = ((code % 256) + 256) % 256;
	cleanup_and_exit(env, args, code);
	return (0);
}
