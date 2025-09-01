/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:27:09 by aaiache           #+#    #+#             */
/*   Updated: 2025/09/01 17:48:59 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *substr(const char *src, int start, int len)
{
    char *res = malloc(len + 1);
    ft_strncpy(res, src + start, len);
    res[len] = '\0';
    return res;
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
	int		start;
	char	*value;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (is_quote(line[i]))
		{
			if ((i = parse_quoted(line, i, line[i], &value)) == -1)
			{
				printf("Error: unclosed quote\n");
				return (NULL);
			}
			tokens = add_token(tokens, value);
		}
		else if (is_special(line[i]))
		{
			if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i])
			{
				value = substr(line, i, 2);
				i += 2;
			}
			else
			{
				value = substr(line, i, 1);
				i += 1;
			}
			tokens = add_token(tokens, value);
		}
		else
		{
			start = i;
			while (line[i] && !is_space(line[i]) && !is_special(line[i]) && !is_quote(line[i]))
				i++;
			value = substr(line, start, i - start);
			tokens = add_token(tokens, value);
		}
	}
	return (tokens);
}
