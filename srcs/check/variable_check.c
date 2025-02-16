/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:29 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/16 17:15:13 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_var_helper(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->input[i])
	{
		if ((*token_node)->input[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

int	check_variable(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		printf("syntax error: missing command before pipe");
		return (1);
	}
	while (temp)
	{
		check_var_helper(&temp);
		if (check_sequence(&temp) == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}

bool	var_valid(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}
