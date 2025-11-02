/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:45:57 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 16:54:08 by xx               ###   ########.fr       */
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
	cmd->heredoc = 0;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	cmd->cmd_name = NULL;
	return (cmd);
}

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	i--;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

int	is_pipe(char *token)
{
	if (token && !ft_strcmp(token, "|"))
		return (1);
	return (0);
}

int	is_redirection(char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token,
			"<<") || !ft_strcmp(token, ">>"))
		return (1);
	return (0);
}
