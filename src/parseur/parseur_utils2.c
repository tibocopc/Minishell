/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 16:55:47 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_input_redir(t_cmd *cmd, char *file)
{
	cmd->input_redir = ft_strdup(file);
}

void	set_output_redir(t_cmd *cmd, char *file, int append)
{
	cmd->output_redir = ft_strdup(file);
	cmd->append = append;
}

static char	**create_new_args(char **old_args, char *arg, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(old_args[i]);
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	return (new_args);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		count;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = create_new_args(cmd->args, arg, count);
	if (!new_args)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	cmd->args = new_args;
	if (!cmd->cmd_name)
		cmd->cmd_name = ft_strdup(arg);
}
