/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:34:17 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/19 18:21:30 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*ft_newlst(char *content)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return (0);
	new->value = content;
	new->next = NULL;
	return (new);
}

t_env_list	*ft_lastlst(t_env_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstaddback(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lastlst(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}


t_env_list	*set_env(char **envp)
{
	t_env_list		*myenv;
	int			i;
	int j;

	j = 0;
	while (envp[j])
		j++;
	myenv = NULL;
	i = 0;
	while (i < j)
	{
		if (i == 0)
			myenv = ft_newlst(envp[i]);
		else
			ft_lstaddback(&myenv, ft_newlst(envp[i]));
		i++;
	}
	return (myenv);
}

