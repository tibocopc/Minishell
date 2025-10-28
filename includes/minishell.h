/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:32:09 by aaiache           #+#    #+#             */
/*   Updated: 2025/10/15 17:47:25 by xx               ###   ########.fr       */
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

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	char				*cmd_name;
	char				**args;
	char				*input_redir;
	char				*output_redir;
	int					append;
	struct s_cmd		*next;
}						t_cmd;

//----------------------BUILTINS-----------------------//
void					check_cd(char **tab);
void					check_pwd(char **tab);
void					ft_exit(char **args);
void					ft_echo(char **tab);
void					ft_env(t_env_list *myenv);

//------------------------SRC-------------------------//
t_env_list				*set_env(char **envp);
t_env_list				*set_env(char **envp);

//----------------------LEXER-------------------------//
t_token					*lexer(const char *line);
int						is_special(char c);
int						is_space(char c);
int						is_quote(char c);
void					print_tokens(t_token *t);
t_token					*add_token(t_token *head, char *val);
int						is_double_quote(char c);

//--------------------PARSEUR------------------------//
t_cmd					*init_new_cmd(void);
int						is_pipe(const char *token);
int						is_redirection(const char *token);
int						add_arg(t_cmd *cmd, char *arg);
t_cmd					*parse_tokens(t_token *tokens);
void					free_cmd_list(t_cmd *cmds);
void					free_tokens(t_token *tokens);
void					exec_builtins(t_cmd *cmd, t_env_list *myenv);
void					expand_tokens(t_cmd *cmd, t_env_list *myenv,
							int last_status);

#endif
