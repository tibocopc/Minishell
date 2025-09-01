/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:58:44 by aaiache           #+#    #+#             */
/*   Updated: 2025/09/01 18:28:07 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_redirection(t_cmd *cmd, t_token *tok)
{
    char *op;
    char *file;

    op = tok->value;
    if (tok->next)
        file = tok->next->value;
    else
        tok->next = NULL;
    if (!file)
    {
        fprintf(stderr, "Syntax error near unexpected token `newline`\n");
        return;
    }
    if (ft_strcmp(op, "<") == 0)
        cmd->input_redir = ft_strdup(file);
    else if (strcmp(op, ">") == 0)
    {
        cmd->output_redir = ft_strdup(file);
        cmd->append = 0;
    }
    else if (strcmp(op, ">>") == 0)
    {
        cmd->output_redir = ft_strdup(file);
        cmd->append = 1;
    }
    else if (strcmp(op, "<<") == 0)
    {
    }
}

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *head;
    t_cmd *curr;

    head = NULL;
    curr = NULL;
    while (tokens)
    {
        t_cmd *new = init_new_cmd();
        while (tokens && !is_pipe(tokens->value))
        {
            if (is_redirection(tokens->value))
            {
                handle_redirection(new, tokens);
                tokens = tokens->next->next;
            }
            else
            {
                add_arg(new, tokens->value);
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
    return head;
}