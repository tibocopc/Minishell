/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:22:57 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 19:21:23 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "pwd") || !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset") || !ft_strcmp(cmd_name, "env")
		|| !ft_strcmp(cmd_name, "exit"))
	{
		return (1);
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd, char ***env)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(cmd->args, *env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args, 0, env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, env));
	return (0);
}
