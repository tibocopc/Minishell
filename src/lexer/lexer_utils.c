/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 17:58:46 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_quote(const char *line, int *i, t_token *tokens)
{
	char	*value;
	char	*quoted;
	char	quote;
	int		parse_result;

	quote = line[*i];
	parse_result = parse_quoted(line, *i, line[*i], &value);
	*i = parse_result;
	if (*i == -1)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (NULL);
	}
	quoted = malloc(ft_strlen(value) + 3);
	quoted[0] = quote;
	ft_strlcpy(quoted + 1, value, ft_strlen(value) + 1);
	quoted[ft_strlen(value) + 1] = quote;
	quoted[ft_strlen(value) + 2] = '\0';
	free(value);
	return (add_token(tokens, quoted));
}

t_token	*handle_special(const char *line, int *i, t_token *tokens)
{
	char	*value;

	if ((line[*i] == '>' || line[*i] == '<') && line[*i + 1] == line[*i])
	{
		value = substr(line, *i, 2);
		*i += 2;
	}
	else
	{
		value = substr(line, *i, 1);
		*i += 1;
	}
	return (add_token(tokens, value));
}

t_token	*handle_word(const char *line, int *i, t_token *tokens)
{
	char	*value;
	int		start;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_special(line[*i])
		&& !is_quote(line[*i]))
		(*i)++;
	value = substr(line, start, *i - start);
	return (add_token(tokens, value));
}
