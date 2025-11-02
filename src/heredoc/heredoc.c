/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by xx                #+#    #+#             */
/*   Updated: 2025/11/02 16:31:12 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_delimiter(char *line, char *delim)
{
	int	len;

	if (!line || !delim)
		return (1);
	len = ft_strlen(delim);
	if (ft_strncmp(line, delim, len) == 0 && line[len] == '\n')
		return (1);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("minishell"), -1);
	set_shell_mode(MODE_HEREDOC);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	set_shell_mode(MODE_PROMPT);
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
