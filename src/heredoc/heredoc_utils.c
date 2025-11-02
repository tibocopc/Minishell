/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:00:00 by xx                #+#    #+#             */
/*   Updated: 2025/11/02 16:29:56 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_eof_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

static int	check_delimiter(char *line, char *delimiter)
{
	int	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, len) == 0)
	{
		if (line[len] == '\n' || line[len] == '\0')
			return (1);
	}
	return (0);
}

static int	write_heredoc_line(char *line, int write_fd, char *delimiter)
{
	if (!line)
	{
		handle_eof_heredoc(delimiter);
		return (1);
	}
	if (check_delimiter(line, delimiter))
	{
		free(line);
		return (1);
	}
	if (write(write_fd, line, ft_strlen(line)) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

int	execute_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	int		result;
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell"), -1);
	set_shell_mode(MODE_HEREDOC);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		result = write_heredoc_line(line, pipe_fd[1], delimiter);
		if (result != 0)
		{
			if (result == -1)
				close(pipe_fd[0]);
			break ;
		}
	}
	close(pipe_fd[1]);
	set_shell_mode(MODE_PROMPT);
	if (result == -1)
		return (-1);
	return (pipe_fd[0]);
}
