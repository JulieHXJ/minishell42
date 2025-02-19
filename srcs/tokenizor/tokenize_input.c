/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:03:15 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/19 18:04:06 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizor(t_shell *data, char *str)
{
	int	i;
	int	len;
	int	start;
	int	status;

	i = -1;
	start = 0;
	len = ft_strlen(str);
	status = DEFAULT;
	while (++i <= len)
	{
		status = set_quote_status(status, str, i);
		if (status == DEFAULT)
			start = word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}

//list helper function
void	remove_empty(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->type == VAR && temp->input[0] == '\0'
			&& temp->var_check == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			remove_token(temp->prev, &free_ptr);
		}
		else
			temp = temp->next;
	}
}
