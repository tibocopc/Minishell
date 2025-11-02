/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/02 16:54:39 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_commands(t_cmd *cmds, char ***myenv, int *exit_status)
{
	if (is_exit_cmd(cmds) && !cmds->next)
		handle_exit(cmds, myenv);
	else if (is_exit_cmd(cmds) && cmds->next)
	{
		free_cmds(cmds);
		return ;
	}
	if (!cmds->next)
		exec_command(cmds, myenv, exit_status);
	else
		exec_commands(cmds, myenv, exit_status);
}

void	process_input(char *input, char ***myenv, int *exit_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(input);
	if (tokens)
	{
		add_history(input);
		if (pipe_syntax(tokens) == 1)
		{
			free_tokens(tokens);
			return ;
		}
		cmds = parse_tokens(tokens);
		free_tokens(tokens);
		if (cmds)
		{
			execute_all_heredocs(cmds);
			expand_tokens(cmds, *myenv, exit_status);
		}
		if (cmds && ((cmds->args && cmds->args[0]) || cmds->input_redir
				|| cmds->output_redir))
			execute_commands(cmds, myenv, exit_status);
		free_cmds(cmds);
	}
}
