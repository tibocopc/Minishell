/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:33:29 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/19 17:54:19 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd_env(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
	if (new_pwd)
	{
		setenv("PWD", new_pwd, 1);
		free(new_pwd);
	}
}

int	ft_cd(char *wd)
{
	char	*path;
	char	*old_pwd;

	if (wd == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = wd;
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	update_pwd_env(old_pwd);
	free(old_pwd);
	return (0);
}

void	check_cd(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments", 1);
		return ;
	}
	if (i == 1)
		ft_cd(NULL);
	else
		ft_cd(tab[1]);
}