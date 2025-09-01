/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:08:22 by aaiache           #+#    #+#             */
/*   Updated: 2025/09/01 17:41:11 by aaiache          ###   ########.fr       */
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

void	add_arg(t_cmd *cmd, char *arg)
{
	int count;
	int i;
	char **new_args;

	i = 0;
	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
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
		cmd->cmd_name = strdup(arg);
}