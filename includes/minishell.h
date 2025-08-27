/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:32:09 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/20 12:09:12 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*value;
}						t_env_list;

//----------------------BUILTINS-----------------------//
void					check_cd(char **tab);
void					check_pwd(char **tab);
void					ft_exit(char **args);
void					ft_echo(char **tab);
void					ft_env(t_env_list *myenv);

//------------------------SRC-------------------------//
t_env_list				*set_env(char **envp);
t_env_list				*set_env(char **envp);

#endif