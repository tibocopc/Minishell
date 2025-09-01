/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:44:27 by aaiache           #+#    #+#             */
/*   Updated: 2025/08/27 16:24:50 by aaiache          ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char *input;
	t_env_list *myenv;

	if (ac > 1)
	{
		printf("minishell: %s: No such file or directory", av[1]);
		exit (127);
	}
	myenv = set_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (input[0] != '\0')
		{
			add_history(input);
			t_token *tokens = lexer(input);
			if (tokens)
				print_tokens(tokens);
		}
	}
	return (0);
}



			// tab = ft_split(input, ' ');
			// retour = parse(tab, myenv);
			// free(input);
			// free(tab);