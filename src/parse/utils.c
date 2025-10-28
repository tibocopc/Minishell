/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:08:22 by aaiache           #+#    #+#             */
/*   Updated: 2025/09/19 13:21:56 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_redir = NULL;
	cmd->output_redir = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	cmd->cmd_name = NULL;
	return (cmd);
}
int	is_pipe(const char *token)
{
	if (token && !ft_strcmp(token, "|"))
		return (1);
	return (0);
}

int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token,
			"<<") || !ft_strcmp(token, ">>"))
		return (1);
	return (0);
}

int	add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	int		i;
	char	**new_args;

	i = 0;
	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (1);
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	if (!cmd->cmd_name)
		cmd->cmd_name = ft_strdup(arg);
	return (0);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
			{
				free(cmds->args[i]);
				i++;
			}
			free(cmds->args);
		}
		if (cmds->cmd_name)
			free(cmds->cmd_name);
		if (cmds->input_redir)
			free(cmds->input_redir);
		if (cmds->output_redir)
			free(cmds->output_redir);
		free(cmds);
		cmds = tmp;
	}
}
