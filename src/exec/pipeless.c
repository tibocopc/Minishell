/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:18:15 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 16:54:40 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->heredoc_fd != -1)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	else if (cmd->input_redir)
	{
		if (handle_input_redir(cmd->input_redir) < 0)
			return (-1);
	}
	if (cmd->output_redir)
	{
		if (handle_output_redir(cmd->output_redir, cmd->append) < 0)
			return (-1);
	}
	return (0);
}

static void	exec_child_process(t_cmd *cmd, char ***envp)
{
	char	*path;

	set_child_signals_default();
	if (handle_redirections(cmd) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, envp));
	path = get_path(cmd->args[0], *envp);
	if (!path)
		exit(127);
	if (execve(path, cmd->args, *envp) < 0)
	{
		perror(cmd->args[0]);
		exit(1);
	}
}

static int	validate_command(t_cmd *cmd, char ***envp, int *exit_status)
{
	char	*path;

	if (!cmd || ((!cmd->args || !cmd->args[0]) && !cmd->input_redir
			&& !cmd->output_redir))
		return (0);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0])
		&& !cmd->input_redir && !cmd->output_redir)
	{
		*exit_status = exec_builtin(cmd, envp);
		return (0);
	}
	if (cmd->args && cmd->args[0] && !is_builtin(cmd->args[0]))
	{
		path = get_path(cmd->args[0], *envp);
		if (!path)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			*exit_status = 127;
			return (0);
		}
		free(path);
	}
	return (1);
}

void	exec_command(t_cmd *cmd, char ***envp, int *exit_status)
{
	pid_t	pid;
	int		status;

	if (!validate_command(cmd, envp, exit_status))
		return ;
	set_shell_mode(MODE_EXEC);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		set_shell_mode(MODE_PROMPT);
		return ;
	}
	if (pid == 0)
		exec_child_process(cmd, envp);
	else
	{
		waitpid(pid, &status, 0);
		*exit_status = exitcode_from_waitstatus(status, 1);
		set_shell_mode(MODE_PROMPT);
	}
}
