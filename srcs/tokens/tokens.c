/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:03:15 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/18 18:06:17 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(t_shell *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			ft_printf("unexpected EOF while looking for matching \"\n");
		else if (status == SQUOTE)
			ft_printf("unexpected EOF while looking for matching \'\n");
		ft_printf("syntax error (unexpected end of file)\n");
		return (1);
	}
	return (0);
}
