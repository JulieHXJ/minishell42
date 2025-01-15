/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:12:29 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/15 19:35:59 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	variable_check(t_token **token_node)
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

int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		ft_printf("syntax error near unexpected token");//////changed
		return (1);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == 1)
			return (1);
		temp = temp->next;
	}
	return (1);
}
