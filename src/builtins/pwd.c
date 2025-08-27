/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:31:26 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/19 15:25:15 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("pwd");
}

void	check_pwd(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	if (i == 1)
		ft_pwd();
	else
		ft_putstr_fd("pwd: too many arguments", 2);
}