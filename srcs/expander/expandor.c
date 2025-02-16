/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:56:45 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:17:04 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quotestatus(t_token **token_node, char c)
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

static bool	is_separator(char c)
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

int	expander(t_shell *data, t_token **token_lst)
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
				update_quotestatus(&temp, temp->input[i]);
				if (temp->input[i] == '$' && is_separator(temp->input[i
							+ 1]) == false && between_quotes(temp->input,
						i) == false && (temp->status == DEFAULT
						|| temp->status == DQUOTE))
					replace_var(&temp, retrieve_var(temp, temp->input + i,
							data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*expander_hd(t_shell *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_separator(str[i + 1]) == false
			&& between_quotes(str, i) == false)
			str = replace_val_hd(str, retrieve_var(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
