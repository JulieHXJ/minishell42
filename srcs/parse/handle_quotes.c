/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:32:39 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:00:01 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	quotes_found(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_shell *data)
{
	t_token	*temp;

	temp = data->token_lst;
	while (temp)
	{
		if (quotes_found(temp->input) == true
			&& (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
			delete_quotes(&temp);
		temp = temp->next;
	}
	return (0);
}
