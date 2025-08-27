/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:04:52 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/20 12:09:38 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env_list *myenv)
{
	t_env_list *temp;

	temp = myenv;
	while (temp)
	{
		printf("%s\n", temp->value);
		if (temp->next)
			temp = temp->next;
		else
			break;	
	}
}