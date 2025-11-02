/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:31:28 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 16:28:47 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_shell_mode
{
	MODE_PROMPT,
	MODE_EXEC,
	MODE_HEREDOC
}								t_shell_mode;

typedef struct s_env_list
{
	struct s_env_list			*next;
	char						*value;
}								t_env_list;

typedef struct s_token
{
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_cmd
{
	char						*cmd_name;
	char						**args;
	char						*input_redir;
	char						*output_redir;
	char						*heredoc_delim;
	int							heredoc_fd;
	int							append;
	int							heredoc;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_fork_data
{
	int							prev_fd;
	int							next_fd;
	int							pipe_read_fd;
}								t_fork_data;

//--------------------------ENV---------------------------//
char							**copy_env(char **envp);

//--------------------------MAIN UTILS--------------------//
int								pipe_syntax(t_token *token);
int								is_exit_cmd(t_cmd *cmd);
void							handle_exit(t_cmd *cmds, char ***myenv);
void							process_input(char *input, char ***myenv,
									int *exit_status);

//--------------------------CLEANUP-----------------------//
void							free_tokens(t_token *tokens);
void							free_cmd(t_cmd *cmd);
void							free_cmds(t_cmd *cmds);
void							free_env(char **env);

//----------------------------LEXER--------------------//
char							*substr(const char *src, int start, int len);
int								parse_quoted(const char *line, int i, char c,
									char **value);
t_token							*lexer(const char *line);
t_token							*handle_quote(const char *line, int *i,
									t_token *tokens);
t_token							*handle_special(const char *line, int *i,
									t_token *tokens);
t_token							*handle_word(const char *line, int *i,
									t_token *tokens);
int								is_special(char c);
int								is_quote(char c);
int								is_space(char c);
void							print_tokens(t_token *t);
t_token							*add_token(t_token *head, char *val);

//------------------------EXPAND---------------------------//
void							expand_tokens(t_cmd *cmd, char **env,
									int *exit_status);

//------------------------PARSEUR---------------------------//
t_cmd							*init_new_cmd(void);
int								is_pipe(char *token);
int								is_redirection(char *token);
void							add_arg(t_cmd *cmd, char *arg);
void							free_array(char **tab);
void							set_input_redir(t_cmd *cmd, char *file);
void							set_output_redir(t_cmd *cmd, char *file,
									int append);
int								handle_redirection(t_cmd *cmd, t_token *tok);
t_cmd							*parse_tokens(t_token *tokens);

//----------------------EXEC------------------------------//
int								handle_redirections(t_cmd *cmd);
int								handle_input_redir(char *file);
int								handle_output_redir(char *file, int append);
void							exec_command(t_cmd *cmd, char ***envp,
									int *exit_status);
int								handle_redirections_mp(t_cmd *cmd);
void							exec_commands(t_cmd *cmds, char ***my_env,
									int *exit_status);
void							handle_child(t_cmd *cmd, int prev_fd,
									int next_fd, char **my_env);
void							setup_pipe_fds(int prev_fd, int next_fd);
void							exec_pipe_child(t_cmd *cmd, int prev_fd,
									int next_fd, char ***env);
int								create_pipe_if_needed(t_cmd *curr,
									int pipe_fd[2]);
int								get_pipe_read_fd(int next_fd, int *pipe_fd);
void							fork_and_exec(t_cmd *curr, t_fork_data *data,
									char ***my_env);
void							handle_pipe_fds(int *prev_fd, int pipe_fd[2],
									t_cmd *curr);
// PATH
char							*get_path(char *cmd, char **env);
char							*search_path_in_dirs(char *cmd, char **allpath);

//--------------------------HEREDOC---------------------//
int								handle_heredoc(char *delimiter);
int								execute_heredoc(char *delimiter);
void							execute_all_heredocs(t_cmd *cmds);

//--------------------------SIGNALS---------------------//
void							install_heredoc_child_handlers(void);
void							set_shell_mode(t_shell_mode mode);
void							set_prompt_mode(void);
void							set_exec_mode(void);
void							sigint_prompt(int sig);
void							set_child_signals_default(void);
int								exitcode_from_waitstatus(int status,
									int print_msg);

//--------------------------EXPANSION--------------------//
int								ft_isalnum_or_underscore(char c);
int								ft_strlen_while(char *s, int (*f)(char));
void							free_both(char *a, char *b);
char							*get_env_value(char **env, char *var_name);
char							*expand_status(char *expanded, int last_status);
char							*expand_variable(char *expanded, char *dollar,
									char **env);

//--------------------------BUILTINS---------------------//
int								is_builtin(char *cmd_name);
int								exec_builtin(t_cmd *cmd, char ***env);
int								find_env_index(char **env, const char *key,
									size_t len);
void							copy_env_without_index(char **new_env,
									char **old_env, int skip);
// PWD
int								ft_pwd(void);
void							check_pwd(char **tab);
// ECHO
int								ft_echo(char **args);
// ENV
int								ft_env(char **args, char **env);
// EXIT
int								ft_exit(char **args, int is_child, char ***env);
// CD
int								ft_cd(char **args, char ***env);
// EXPORT
int								update_or_add_env(char ***env, char *key,
									char *value);
int								add_new_var(char ***env, char *var);
int								find_var_index(char **env, const char *key);
char							*join_key_value(const char *key,
									const char *value);
int								is_valid_identifier(const char *str);
void							print_export(char **env);
int								ft_export(char **args, char ***env);
// UNSET
int								ft_unset(char **args, char ***env);

#endif