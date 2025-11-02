/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:27:09 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/01 18:27:18 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*substr(const char *src, int start, int len)
{
	char	*res;

	res = malloc(len + 1);
	ft_strncpy(res, src + start, len);
	res[len] = '\0';
	return (res);
}

int	parse_quoted(const char *line, int i, char c, char **value)
{
	int	start;

	i++;
	start = i;
	while (line[i] && line[i] != c)
		i++;
	if (!line[i])
	{
		*value = NULL;
		return (-1);
	}
	*value = ft_substr(line, start, i - start);
	return (i + 1);
}

t_token	*lexer(const char *line)
{
	int		i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		if (is_quote(line[i]))
			tokens = handle_quote(line, &i, tokens);
		else if (is_special(line[i]))
			tokens = handle_special(line, &i, tokens);
		else
			tokens = handle_word(line, &i, tokens);
		if (!tokens && is_quote(line[i - 1]))
			return (NULL);
	}
	return (tokens);
}
