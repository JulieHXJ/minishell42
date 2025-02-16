/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:04:07 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/13 17:22:40 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigquit_ignore(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

static void	reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Ignores SIGQUIT (Ctrl-), let SIGINT (Ctrl-C) to reset the prompt
 */
void	preset_signals(void)
{
	struct sigaction	act;

	sigquit_ignore();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	signals_during_exec(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
