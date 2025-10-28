/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:58:44 by aaiache           #+#    #+#             */
/*   Updated: 2025/10/13 14:10:29 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirection(t_cmd *cmd, t_token **ptok)
{
	t_token	*tok;
	char	*op;
	char	*file;

	tok = *ptok;
	op = tok->value;
	file = NULL;
	if (tok->next)
		file = tok->next->value;
	if (!file || is_pipe(file) || is_redirection(file))
	{
		if (file)
		{
			fprintf(stderr, "syntax error near unexpected token `%s`\n", file);
			return (-1);
		}
		else
		{
			fprintf(stderr, "syntax error near unexpected token `newline`\n");
			return (-1);
		}
		*ptok = tok->next->next;
		return (-1);
	}
	if (ft_strcmp(op, "<") == 0)
	{
		if (cmd->input_redir)
		{
			free(cmd->input_redir);
			cmd->input_redir = NULL;
		}
		cmd->input_redir = ft_strdup(file);
	}
	else if (ft_strcmp(op, ">") == 0)
	{
		if (cmd->output_redir)
		{
			free(cmd->output_redir);
			cmd->output_redir = NULL;
		}
		cmd->output_redir = ft_strdup(file);
		cmd->append = 0;
	}
	else if (ft_strcmp(op, ">>") == 0)
	{
		if (cmd->output_redir)
		{
			free(cmd->output_redir);
			cmd->output_redir = NULL;
		}
		cmd->output_redir = ft_strdup(file);
		cmd->append = 1;
	}
	else if (ft_strcmp(op, "<<") == 0)
	{
	}
	*ptok = tok->next->next;
	return (0);
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
		new = init_new_cmd();
		while (tokens && !is_pipe(tokens->value))
		{
			if (is_redirection(tokens->value))
			{
				if (handle_redirection(new, &tokens) < 0)
				{
					(free_cmd_list(curr));
					return (NULL);
				}
			}
			else
			{
				if (add_arg(new, tokens->value) < 0)
					break ;
				tokens = tokens->next;
			}
		}
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
