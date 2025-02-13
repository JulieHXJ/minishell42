/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:03:15 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/13 19:21:17 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 */
int	tokenize(t_shell *data, char *str)
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
