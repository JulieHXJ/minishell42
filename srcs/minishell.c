/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/26 17:55:25 by xhuang           ###   ########.fr       */
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

static bool	check_input(int argc)
{
	if (argc != 1)
		return (instruction_msg(false));
	return (true);
}

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

void	run_minishell(t_shell *minishell,char **argv)
{


	while (1)
	{
		set_signals();//handle ctrl-\ and ctrl-c
		minishell->input = readline(PROMPT);
		set_signals_noninteractive();
		if (parse_input(minishell) == true)
			global_exit_code = execute(minishell, argv);
		else
			global_exit_code = 1;
		free_shell(minishell, false);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;
	(void)argv;
	if (argc != 1)
		return (instruction_msg(false));
	ft_memset(&minishell, 0, sizeof(t_shell));
	if (!check_input(argc) || !init_shell(&minishell, envp))
		terminate_shell(NULL, EXIT_FAILURE);
	run_minishell(&minishell, argv);
	terminate_shell(&minishell, global_exit_code);	
	return (0);
}
