/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xx <xx@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:00:00 by tniagolo          #+#    #+#             */
/*   Updated: 2025/11/01 16:55:43 by xx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_child_signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static int	handle_sigint(int print_msg)
{
	if (print_msg)
		write(1, "\n", 1);
	return (128 + SIGINT);
}

static int	handle_sigquit(int cored, int print_msg)
{
	if (print_msg)
	{
		if (cored)
			write(2, "Quit (core dumped)\n", 19);
		else
			write(2, "Quit\n", 5);
	}
	return (128 + SIGQUIT);
}

static int	sig_exitcode(int status, int print_msg)
{
	int	sig;
	int	cored;

	sig = WTERMSIG(status);
	cored = WCOREDUMP(status);
	if (sig == SIGINT)
		return (handle_sigint(print_msg));
	if (sig == SIGQUIT)
		return (handle_sigquit(cored, print_msg));
	return (128 + sig);
}

int	exitcode_from_waitstatus(int status, int print_msg)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (sig_exitcode(status, print_msg));
	return (1);
}
