/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/15 17:07:19 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_exit_code = 0;

void set_exit_code(int code) {
    global_exit_code = code;  // Set the global variable
}

static bool	instructions_msg(bool value)
{
	ft_putendl_fd("Input format: ./minishell", 2);
	return (value);
}

static bool	check_input(int argc)
{
	if (argc != 1)
		return (instructions_msg(false));
	return (true);
}

void	terminate_shell(t_shell *data, int exit_code)
{
	if (data)
	{
		if (data->command && data->command->pipe)
			close_fds(data->command, true);//todo
		free_shell(data, true);//todo
	}
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;
	(void)argv;

	ft_memset(&minishell, 0, sizeof(t_shell));
	if (check_input(argc) || init_shell(&minishell, envp))
	{
		//run_minishell(&minishell);
		terminate_shell(&minishell, global_exit_code);	
	}
	else
		terminate_shell(NULL, EXIT_FAILURE);
	return (0);
}
