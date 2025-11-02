/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:32:03 by aaiache           #+#    #+#             */
/*   Updated: 2025/11/02 17:05:33 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	shell_loop(char ***myenv, int *exit_status)
{
	char	*input;

	while (1)
	{
		set_shell_mode(MODE_PROMPT);
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
			g_signal = 0;
		if (input[0] != '\0')
			process_input(input, myenv, exit_status);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**myenv;
	int		exit_status;

	(void)ac;
	(void)av;
	exit_status = 0;
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: stdin must be a terminal\n", 2);
		return (1);
	}
	myenv = copy_env(envp);
	shell_loop(&myenv, &exit_status);
	free_env(myenv);
	return (exit_status);
}
