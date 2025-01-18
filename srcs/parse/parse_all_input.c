/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:33:19 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/18 19:14:57 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	input_is_space(char *input)
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

bool	parse_input(t_shell *data)
{
	// if (data->input == NULL)
	// 	exit_builtin(data, NULL);
	if (ft_strcmp(data->input, "\0") == 0)
		return (false);
	else if (input_is_space(data->input))
		return (true);
	// add_history(data->input);
	if (tokenization(data, data->input) == 1)
		return (false);
	if (data->token->type == END)
		return (false);
	if (check_if_var(&data->token) == 1)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	handle_commands(data, data->token);
	return (true);
}
