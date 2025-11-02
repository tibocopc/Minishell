/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/02 16:54:33 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_pipe_fds(int prev_fd, int next_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (next_fd != -1)
	{
		dup2(next_fd, STDOUT_FILENO);
		close(next_fd);
	}
}

void	exec_pipe_child(t_cmd *cmd, int prev_fd, int next_fd, char ***env)
{
	char	*path;

	set_child_signals_default();
	setup_pipe_fds(prev_fd, next_fd);
	if (handle_redirections_mp(cmd) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, env));
	path = get_path(cmd->cmd_name, *env);
	if (!path)
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(path, cmd->args, *env);
	perror(cmd->args[0]);
	exit(126);
}

int	create_pipe_if_needed(t_cmd *curr, int pipe_fd[2])
{
	if (curr->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		return (pipe_fd[1]);
	}
	return (-1);
}
