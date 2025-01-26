/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:56:45 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/26 16:55:53 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = DEFAULT;
}

static bool	is_separator_next(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	between_quotes(char *s, int i)
{
	if (i > 0)
	{
		if (s[i - 1] == '\"' && s[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}
/*

Example: Transitioning into or out of quoted states.
is_next_char_a_sep: 

var_between_quotes: 

recover_val: Retrieves the value of the variable from the environment or shell data structure.

replace_var: Replaces the $VAR in the token with the expanded value.
*/
int	var_expander(t_shell *data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->input[i])
			{
				quote_status(&temp, temp->input[i]);//Updates the status of the token based on the current character. 
				if (temp->input[i] == '$'
					&& is_separator_next(temp->input[i + 1]) == false //Checks if the character following $ is a separator
					&& between_quotes(temp->input, i) == false //if the $ is between single quotes, where variable expansion is not allowed.
					&& (temp->status == DEFAULT || temp->status == DQUOTE))
					replace_var(&temp, retrieve_var(temp, temp->input + i, data), i); //Replaces the $VAR in the token with the expanded value. Retrieves the value of the variable from the environment or shell data structure.
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*var_expander_hd(t_shell *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_separator_next(str[i + 1]) == false
			&& between_quotes(str, i) == false)
			str = replace_val_hd(str, retrieve_var(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
