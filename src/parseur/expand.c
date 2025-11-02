/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:25:44 by xx                #+#    #+#             */
/*   Updated: 2025/11/01 17:17:51 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dollar(char *expanded, char *dollar, char **env,
		int *exit_status)
{
	char	*cursor;

	if (dollar[1] == '?')
	{
		expanded = expand_status(expanded, *exit_status);
		cursor = dollar + 2;
	}
	else
	{
		expanded = expand_variable(expanded, dollar, env);
		cursor = dollar + 1 + ft_strlen_while(dollar + 1,
				ft_isalnum_or_underscore);
	}
	return (expanded);
}

static char	*perform_expansion(char *arg, char **env, int *exit_status)
{
	char	*cursor;
	char	*dollar;
	char	*expanded;
	char	*prefix;
	char	*tmp;

	cursor = arg;
	expanded = ft_strdup("");
	while (*cursor)
	{
		dollar = ft_strchr(cursor, '$');
		if (!dollar)
			return (tmp = ft_strjoin(expanded, cursor), free(expanded), tmp);
		prefix = ft_substr(cursor, 0, dollar - cursor);
		tmp = ft_strjoin(expanded, prefix);
		free_both(expanded, prefix);
		expanded = handle_dollar(tmp, dollar, env, exit_status);
		cursor = dollar + 1;
		if (dollar[1] == '?')
			cursor++;
		else if (ft_isalnum_or_underscore(dollar[1]))
			cursor += ft_strlen_while(dollar + 1, ft_isalnum_or_underscore);
	}
	return (expanded);
}

static char	*expand_arg(char *arg, char **env, int *exit_status)
{
	size_t	len;
	char	*tmp;
	char	*expanded;

	len = ft_strlen(arg);
	if (arg[0] == '\'' && arg[len - 1] == '\'')
		return (ft_substr(arg, 1, len - 2));
	if (arg[0] == '"' && arg[len - 1] == '"')
	{
		tmp = ft_substr(arg, 1, len - 2);
		expanded = perform_expansion(tmp, env, exit_status);
		free(tmp);
		return (expanded);
	}
	return (perform_expansion(arg, env, exit_status));
}

void	expand_tokens(t_cmd *cmd, char **env, int *exit_status)
{
	t_cmd	*tok;
	int		i;
	char	*expanded;

	tok = cmd;
	while (tok)
	{
		if (tok->args)
		{
			i = 0;
			while (tok->args[i])
			{
				expanded = expand_arg(tok->args[i], env, exit_status);
				free(tok->args[i]);
				tok->args[i] = expanded;
				i++;
			}
		}
		tok = tok->next;
	}
}
