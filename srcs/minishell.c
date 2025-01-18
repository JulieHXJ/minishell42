/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 19:12:56 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_exit_code = 0;

void set_exit_code(int code) 
{
    global_exit_code = code;  // update the global variable
}

static bool	instruction_msg(bool value)
{
	ft_putendl_fd("Input format: ./minishell", 2);
	return (value);
}

// static bool	check_input(int argc)
// {
// 	if (argc != 1)
// 		return (instruction_msg(false));
// 	return (true);
// }

void	terminate_shell(t_shell *minishell, int exit_code)
{
	if (minishell)
	{
		if (minishell->command && minishell->command->pipe)
			close_fds(minishell->command, true);//todo
		free_shell(minishell, true);//todo
	}
	exit(exit_code);
}

void	run_minishell(t_shell *minishell)
{
	// Parse the input (split into arguments)
	if (parse_input(minishell) == true)
	{
		// Check if the command is a built-in
		// handle_buildins()
		// Execute external command
		global_exit_code = execute(minishell);/////////////to do
	}
	else
		global_exit_code = 1;
	free_shell(minishell, false);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;
	(void)argv;
	if (argc != 1)
		return (instruction_msg(false));
	ft_memset(&minishell, 0, sizeof(t_shell));
	if (init_shell(&minishell, envp))
	{
		while (1)
		{
			set_signals();//handle ctrl-\ and ctrl-c
			minishell.input = readline(PROMPT);
			if (!minishell.input)
			{
				write(1, "exit\n", 5); //exit message
				break;
			}
			if (*minishell.input)
			{
				add_history(minishell.input);
				run_minishell(&minishell);
			}
			// free(minishell.input);
		}
		terminate_shell(&minishell, global_exit_code);	
	}
	else
		terminate_shell(NULL, EXIT_FAILURE);
	return (0);
}
