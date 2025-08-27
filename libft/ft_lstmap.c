/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:37:04 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/04 16:12:44 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*current;

	if (!del || !f || !lst)
		return (0);
	current = ft_lstnew(f(lst->content));
	if (!current)
		return (0);
	res = current;
	lst = lst->next;
	while (lst)
	{
		current->next = ft_lstnew(f(lst->content));
		if (!current->next)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		current = current->next;
		lst = lst->next;
	}
	current->next = 0;
	return (res);
}
