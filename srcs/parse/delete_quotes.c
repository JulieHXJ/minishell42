/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:34:12 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:58:48 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	inner_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE) || (str[i] == '\"'
				&& status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

static void	to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->input[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->input[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

static bool	if_default(t_token **token_node, int i)
{
	if (((*token_node)->input[i] == '\'' || (*token_node)->input[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	to_default(t_token **token_node, int *i)
{
	if (((*token_node)->input[*i] == '\'' && (*token_node)->status == SQUOTE)
		|| ((*token_node)->input[*i] == '\"'
			&& (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	delete_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * inner_len((*token_node)->input, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->input[i])
	{
		if (if_default(token_node, i) == true)
		{
			to_quote(token_node, &i);
			continue ;
		}
		else if (to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->input[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->input);
	(*token_node)->input = new_line;
	(*token_node)->joined = true;
	return (0);
}
