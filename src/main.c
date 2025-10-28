/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:44:27 by aaiache           #+#    #+#             */
/*   Updated: 2025/10/15 20:51:45 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse(char **tab, t_env_list *myenv)
{
	if (ft_strcmp(tab[0], "pwd") == 0)
		check_pwd(tab);
	else if (ft_strcmp(tab[0], "cd") == 0)
		check_cd(tab);
	else if (ft_strcmp(tab[0], "exit") == 0)
		ft_exit(tab);
	else if (ft_strcmp(tab[0], "echo") == 0)
		ft_echo(tab);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(myenv);
	return (1);
}

void	print_cmds(t_cmd *cmds)
{
	int (i);
	while (cmds)
	{
		printf("=== Nouvelle commande ===\n");
		// Nom de la commande
		if (cmds->cmd_name)
			printf("cmd_name: %s\n", cmds->cmd_name);
		// Arguments
		printf("args:");
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
			{
				printf(" [%s]", cmds->args[i]);
				i++;
			}
		}
		printf("\n");
		// Redirections
		if (cmds->input_redir)
			printf("input_redir: %s\n", cmds->input_redir);
		if (cmds->output_redir)
			printf("output_redir: %s (append=%d)\n", cmds->output_redir,
				cmds->append);
		cmds = cmds->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env_list	*myenv;
	t_token		*tokens;
	t_cmd		*cmd_list;

	if (ac > 1)
	{
		printf("minishell: %s: No such file or directory", av[1]);
		exit(127);
	}
	myenv = set_env(envp);
	while (1)
	{
		input = readline("minishell >");
		if (input[0] != '\0')
		{
			add_history(input);
			tokens = lexer(input);
			cmd_list = parse_tokens(tokens);
			expand_tokens(cmd_list, myenv, 1);
			if (!cmd_list)
				free_tokens(tokens);
			exec_builtins(cmd_list, myenv);
		}
		print_cmds(cmd_list);
	}
	return (0);
}
