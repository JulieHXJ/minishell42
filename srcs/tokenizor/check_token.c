/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:24:44 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/13 19:18:32 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	sequence_check(t_token *token_node)
{
	if (token_node->prev)
	{
		if (token_node->type == PIPE && token_node->prev->type == PIPE)
			return (true);
		if (token_node->type > PIPE && token_node->prev->type > PIPE)
			return (true);
		if (token_node->type == END && token_node->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

int	check_token_list(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (sequence_check(temp) == true)
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				ft_printf("syntax error: newline\n");
			else if (temp->type == END && temp->prev)
				ft_printf("syntax error: %s\n", temp->prev->input);
			else
				ft_printf("syntax error: %s\n", temp->input);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
