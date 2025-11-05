/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/05 16:30:21 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_heredoc_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	sigint_heredoc_parent(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	install_heredoc_child_handlers(void)
{
	signal(SIGINT, sigint_heredoc_child);
	signal(SIGQUIT, SIG_IGN);
}

void	set_shell_mode(t_shell_mode mode)
{
	if (mode == MODE_PROMPT)
		set_prompt_mode();
	else if (mode == MODE_EXEC)
		set_exec_mode();
	else if (mode == MODE_HEREDOC)
	{
		signal(SIGINT, sigint_heredoc_child);
		signal(SIGQUIT, SIG_IGN);
	}
}
