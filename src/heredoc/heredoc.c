/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by xx                #+#    #+#             */
/*   Updated: 2025/11/05 16:48:59 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_delimiter(char *line, char *delim)
{
	int	len;

	if (!line || !delim)
		return (1);
	len = ft_strlen(delim);
	if (ft_strncmp(line, delim, len) == 0 && line[len] == '\0')
		return (1);
	return (0);
}

void	loop_hd(char *delimiter, int *pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || is_delimiter(line, delimiter))
		{
			if (!line)
				handle_eof_heredoc(delimiter);
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell"), close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		install_heredoc_child_handlers();
		loop_hd(delimiter, pipe_fd);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	install_heredoc_parent_handlers();
	waitpid(pid, &status, 0);
	set_prompt_mode();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(pipe_fd[0]), g_signal = SIGINT, -1);
	return (pipe_fd[0]);
}

void	execute_all_heredocs(t_cmd *cmds)
{
	t_cmd	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->heredoc && curr->heredoc_delim)
		{
			curr->heredoc_fd = handle_heredoc(curr->heredoc_delim);
			if (curr->heredoc_fd == -1)
				return ;
		}
		curr = curr->next;
	}
}
