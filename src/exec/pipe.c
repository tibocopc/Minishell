/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:01:41 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 16:54:39 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirections_mp(t_cmd *cmd)
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

static void	exec_loop(t_cmd *cmds, char ***my_env, int *prev_fd)
{
	int			pipe_fd[2];
	t_cmd		*curr;
	t_fork_data	data;

	curr = cmds;
	while (curr)
	{
		data.next_fd = create_pipe_if_needed(curr, pipe_fd);
		data.prev_fd = *prev_fd;
		data.pipe_read_fd = get_pipe_read_fd(data.next_fd, pipe_fd);
		fork_and_exec(curr, &data, my_env);
		handle_pipe_fds(prev_fd, pipe_fd, curr);
		curr = curr->next;
	}
}

void	exec_commands(t_cmd *cmds, char ***my_env, int *exit_status)
{
	int	prev_fd;
	int	status;

	prev_fd = -1;
	set_shell_mode(MODE_EXEC);
	exec_loop(cmds, my_env, &prev_fd);
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(&status) > 0)
		;
	*exit_status = exitcode_from_waitstatus(status, 1);
	set_shell_mode(MODE_PROMPT);
}

void	handle_child(t_cmd *cmd, int prev_fd, int next_fd, char **my_env)
{
	char	*path;

	setup_pipe_fds(prev_fd, next_fd);
	if (handle_redirections_mp(cmd) < 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, &my_env));
	path = get_path(cmd->cmd_name, my_env);
	if (!path)
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(path, cmd->args, my_env);
	perror(cmd->args[0]);
	exit(126);
}
