/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 19:31:22 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_syntax(t_token *token)
{
	t_token	*tmp;
	char	prev;

	tmp = token;
	prev = tmp->value[0];
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->value[0] == '|')
		{
			if (prev == '<' || prev == '>' || prev == '|')
				return (ft_putstr_fd("syntax error near unexpected token `|'\n",
						2), 1);
		}
		prev = tmp->value[0];
		tmp = tmp->next;
	}
	if (!tmp && prev == '|')
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), 1);
	return (0);
}

int	is_exit_cmd(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

static char	**copy_args(t_cmd *cmds)
{
	char	**args_copy;
	int		i;

	i = 0;
	while (cmds->args[i])
		i++;
	args_copy = malloc(sizeof(char *) * (i + 1));
	if (!args_copy)
		exit(1);
	i = 0;
	while (cmds->args[i])
	{
		args_copy[i] = ft_strdup(cmds->args[i]);
		i++;
	}
	args_copy[i] = NULL;
	return (args_copy);
}

void	handle_exit(t_cmd *cmds, char ***myenv)
{
	char	**args_copy;

	args_copy = copy_args(cmds);
	free_cmds(cmds);
	rl_clear_history();
	ft_exit(args_copy, 0, myenv);
}
