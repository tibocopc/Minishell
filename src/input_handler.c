/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/05 16:27:46 by aaiache          ###   ########.fr       */
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
			return (free_tokens(tokens), (void)0);
		cmds = parse_tokens(tokens);
		free_tokens(tokens);
		if (cmds)
		{
			execute_all_heredocs(cmds);
			if (g_signal == SIGINT)
				return (*exit_status = 130, free_cmds(cmds), (void)0);
			expand_tokens(cmds, *myenv, exit_status);
		}
		if (cmds && ((cmds->args && cmds->args[0]) || cmds->input_redir
				|| cmds->output_redir))
			execute_commands(cmds, myenv, exit_status);
		free_cmds(cmds);
	}
}
