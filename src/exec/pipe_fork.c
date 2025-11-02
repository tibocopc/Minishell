/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 19:31:22 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pipe_read_fd(int next_fd, int *pipe_fd)
{
	if (next_fd != -1)
		return (pipe_fd[0]);
	return (-1);
}

void	fork_and_exec(t_cmd *curr, t_fork_data *data, char ***my_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (data->pipe_read_fd != -1)
			close(data->pipe_read_fd);
		exec_pipe_child(curr, data->prev_fd, data->next_fd, my_env);
	}
}

void	handle_pipe_fds(int *prev_fd, int pipe_fd[2], t_cmd *curr)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (curr->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}
