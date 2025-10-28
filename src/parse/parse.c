#include "../../includes/minishell.h"

void	exec_builtins(t_cmd *cmd, t_env_list *myenv)
{
	if (!cmd || !cmd->cmd_name)
		return ;
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		check_cd(cmd->args);
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		check_pwd(cmd->args);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		ft_env(myenv);
	// // else if (ft_strcmp(cmd->cmd_name,"export") == 0)
	// ft_export(cmd->args,
	// 	myenv);
	// 	// else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
	// 		// ft_unset(cmd->args,
	// 	myenv); // else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
	// 		// ft_exit(cmd->args); // else // exec_external(cmd);
	// 		// fork
}
char	*get_env_value(t_env_list *env, const char *name)
{
	size_t	name_len;
	char	*eq;
	size_t	var_len;

	if (!env || !name)
		return (NULL);
	name_len = ft_strlen(name);
	while (env)
	{
		eq = ft_strchr(env->value, '=');
		if (eq)
		{
			var_len = eq - env->value;
			if (var_len == name_len && ft_strncmp(env->value, name,
					name_len) == 0)
				return (ft_strdup(eq + 1));
		}
		env = env->next;
	}
	return (NULL);
}
int	ft_isalnum_or_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}
int	ft_strlen_while(char *s, int (*f)(char))
{
	int	i;

	i = 0;
	while (s[i] && f(s[i]))
		i++;
	return (i);
}
void	free_both(char *a, char *b)
{
	free(a);
	free(b);
}
static char	*expand_status(char *expanded, int last_status)
{
	char	*tmp;
	char	*status;

	status = ft_itoa(last_status);
	tmp = ft_strjoin(expanded, status);
	free(expanded);
	free(status);
	return (tmp);
}
static char	*expand_variable(char *expanded, char *dollar, t_env_list *env)
{
	char	*var_name;
	char	*val;
	char	*tmp;
	int		j;

	j = 1;
	while (ft_isalnum(dollar[j]) || dollar[j] == '_')
		j++;
	var_name = ft_substr(dollar + 1, 0, j - 1);
	val = get_env_value(env, var_name);
	free(var_name);
	if (!val)
		val = "";
	tmp = ft_strjoin(expanded, val);
	free(expanded);
	return (tmp);
}
static char	*perform_expansion(char *arg, t_env_list *env, int last_status)
{
	char	*cursor;
	char	*dollar;
	char	*expanded;
	char	*prefix;
	char	*tmp;

	cursor = arg;
	expanded = ft_strdup("");
	while (*cursor)
	{
		dollar = ft_strchr(cursor, '$');
		if (!dollar)
			return (tmp = ft_strjoin(expanded, cursor), free(expanded), tmp);
		prefix = ft_substr(cursor, 0, dollar - cursor);
		tmp = ft_strjoin(expanded, prefix);
		free_both(expanded, prefix);
		expanded = tmp;
		if (dollar[1] == '?')
			expanded = expand_status(expanded, last_status), cursor = dollar
				+ 2;
		else
			expanded = expand_variable(expanded, dollar, env), cursor = dollar
				+ 1 + ft_strlen_while(dollar + 1, ft_isalnum_or_underscore);
	}
	return (expanded);
}
static char	*expand_arg(char *arg, t_env_list *env, int last_status)
{
	size_t	len;
	char	*tmp;
	char	*expanded;

	len = ft_strlen(arg);
	if (arg[0] == '\'' && arg[len - 1] == '\'')
		return (ft_substr(arg, 1, len - 2));
	if (arg[0] == '"' && arg[len - 1] == '"')
	{
		tmp = ft_substr(arg, 1, len - 2);
		expanded = perform_expansion(tmp, env, last_status);
		free(tmp);
		return (expanded);
	}
	return (perform_expansion(arg, env, last_status));
}
void	expand_tokens(t_cmd *cmd, t_env_list *env, int last_status)
{
	t_cmd	*tok;
	int		i;
	char	*expanded;

	tok = cmd;
	while (tok)
	{
		i = 0;
		while (tok->args[i])
		{
			expanded = expand_arg(tok->args[i], env, last_status);
			free(tok->args[i]);
			tok->args[i] = expanded;
			i++;
		}
		tok = tok->next;
	}
}
