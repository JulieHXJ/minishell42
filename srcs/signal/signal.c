/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:04:07 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/19 19:39:19 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Ignore the SIGQUIT signals triggered by Ctrl-\.
*
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/**
* @brief Handle the SIGINT signal (Ctrl-C) to reset the prompt.
* 
*/
static void	reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line(); // Notifies the readline library that a new line has been initiated.
	rl_replace_line("", 0); //Clears the current line in the input buffer
	rl_redisplay();// Updates the terminal display to show the new prompt
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/**
* @brief Ignore SIGQUIT and handle SIGINT.
*
*/
void	set_signals(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &reset_prompt;
	sigaction(SIGINT, &act, NULL);
}
