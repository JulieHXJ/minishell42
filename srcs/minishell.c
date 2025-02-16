/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:59:50 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_code = 0;

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

//!!!!!!!handled empty input
static bool	parse_input(t_shell *data)
{
	if (data->input == NULL)
		exit_builtin(data, NULL);//ctrl+D
	else if (!*data->input)
		return (true);//empty input(just enter)
	add_history(data->input);
	if (only_space(data->input))
		return (true);
	if (tokenizor(data, data->input) == 1)
		return (false);
	if (data->token_lst->type == END)
		return (false);
	if (check_variable(&data->token_lst) == 1)
		return (false);
	expander(data, &data->token_lst);
	handle_quotes(data);
	parse_all_type(data, data->token_lst);
	return (true);
}

void	reset_shell(t_shell *mini)
{
	if (!mini)
		return ;
	if (mini->input)
		free_ptr(mini->input);
	if (mini->token_lst)
		free_token(&mini->token_lst, &free_ptr);
	if (mini->cmd_lst)
		free_cmd(&mini->cmd_lst, &free_ptr);
}

void	terminate_shell(t_shell *minishell, int exit_code)
{
	if (minishell)
	{
		if (minishell->cmd_lst && minishell->cmd_lst->io)
			close_fds(minishell->cmd_lst, true);
		free_shell(minishell);
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
			break ;
		if (ft_strcmp(minishell.input, "./minishell") == 0)
			handle_shlvl(&minishell);//if input is "./minishell", SHLVL should grow
		if (parse_input(&minishell))
			g_exit_code = executor(&minishell);
		else
			g_exit_code = 1;
		reset_shell(&minishell);
	}
	terminate_shell(&minishell, g_exit_code);
	return (0);
}
