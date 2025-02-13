/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 21:06:18 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_exit_code = 0;

// void set_exit_code(int code)
// {
//     global_exit_code = code;  // Modify the global variable
// }


static bool	only_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	parse_input(t_shell *data)
{
	if (data->input == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->input, "\0") == 0)
		return (false);
	else if (only_space(data->input))
		return (true);
	add_history(data->input);
	if (tokenize(data, data->input) == 1)
		return (false);
	if (data->token_lst->type == END)
		return (false);
	if (check_if_var(&data->token_lst) == 1)
		return (false);
	var_expander(data, &data->token_lst);
	handle_quotes(data);
	handle_commands(data, data->token_lst);
	return (true);
}
// void	reset_shell(t_shell *mini)
// {
// 	preset_signals();
// 	if (!mini)
// 		return ;
// 	printf("Shell struct address: %p\n", (void*)mini);
//     if (mini->input)
//     {
//         printf("Freeing input at %p\n", (void*)mini->input);
//         free(mini->input);
//     }
//     if (mini->token_lst)
//     {
//         printf("Freeing token_lst at %p\n", (void*)mini->token_lst);
//         free_token(&mini->token_lst);
//     }
//     if (mini->cmd_lst)
//     {
//         printf("Freeing cmd_lst at %p\n", (void*)mini->cmd_lst);
//         free_cmd(&mini->cmd_lst);
//     }
// }

void	terminate_shell(t_shell *minishell, int exit_code)
{
	if (minishell)
	{
		if (minishell->cmd_lst && minishell->cmd_lst->io)
			close_fds(minishell->cmd_lst, true);
		free_shell(minishell, true);
	}
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Input format: ./minishell\n"), 1);
	ft_memset(&minishell, 0, sizeof(t_shell));
	if (!init_shell(&minishell, envp))
		exit(EXIT_FAILURE);
	while (1)
	{
		preset_signals();
		minishell.input = readline(PROMPT);
		signals_during_exec();
		if (!minishell.input)
		{
			ft_printf("EOF\n");
            break ;
		}
		if (parse_input(&minishell))
			global_exit_code = execute(&minishell);
		else
		{
			global_exit_code = 1;
			ft_printf("parsing failed\n");
			
		}
		// reset_shell(&minishell);
		free_shell(&minishell, false);
	}
	terminate_shell(&minishell, global_exit_code);
	return (0);
}
