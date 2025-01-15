/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:33:19 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/15 19:27:51 by amesmar          ###   ########.fr       */
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
	if (data->input == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->input, "\0") == 0)
		return (false);
	else if (input_is_space(data->input))
		return (true);
	add_history(data->input);
	if (tokenization(data, data->input) == 1)
		return (false);
	if (data->token->type == END)
		return (false);
	if (check_if_var(&data->token) == 1)
		return (false);
        ////////////////////////////////to do///////////////////////////
	// var_expander(data, &data->token);
	// handle_quotes(data);
	// create_commands(data, data->token);
	return (true);
}
