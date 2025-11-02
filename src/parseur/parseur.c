/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:46:16 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 17:10:22 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_heredoc(t_cmd *cmd, char *delimiter)
{
	cmd->heredoc = 1;
	cmd->heredoc_delim = ft_strdup(delimiter);
	cmd->heredoc_fd = -1;
}

int	handle_redirection(t_cmd *cmd, t_token *tok)
{
	char	*op;
	char	*file;

	file = NULL;
	op = tok->value;
	if (tok->next)
		file = tok->next->value;
	if (!file || is_pipe(file) || is_redirection(file))
	{
		if (file)
			return (ft_putstr_fd("syntax error near unexpected token `", 2),
				ft_putstr_fd(file, 2), ft_putstr_fd("`\n", 2), -1);
		else
			return (ft_putstr_fd("syntax error near unexpected", 2),
				ft_putstr_fd("token `newline`\n", 2), -1);
	}
	if (ft_strcmp(op, "<") == 0)
		set_input_redir(cmd, file);
	else if (ft_strcmp(op, ">") == 0)
		set_output_redir(cmd, file, 0);
	else if (ft_strcmp(op, ">>") == 0)
		set_output_redir(cmd, file, 1);
	else if (ft_strcmp(op, "<<") == 0)
		init_heredoc(cmd, file);
	return (0);
}

static int	process_token(t_cmd *cmd, t_token **tokens)
{
	if (is_redirection((*tokens)->value))
	{
		if (handle_redirection(cmd, *tokens) < 0)
			return (-1);
		*tokens = (*tokens)->next;
		if (!*tokens)
			return (0);
		*tokens = (*tokens)->next;
	}
	else
	{
		add_arg(cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	return (0);
}

static t_cmd	*parse_single_cmd(t_token **tokens)
{
	t_cmd	*cmd;

	cmd = init_new_cmd();
	if (!cmd)
		return (NULL);
	while (*tokens && !is_pipe((*tokens)->value))
	{
		if (process_token(cmd, tokens) < 0)
		{
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new;

	head = NULL;
	curr = NULL;
	while (tokens)
	{
		new = parse_single_cmd(&tokens);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		if (tokens && is_pipe(tokens->value))
			tokens = tokens->next;
	}
	return (head);
}
