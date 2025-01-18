/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:39:34 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 19:15:50 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_pipes(t_shell *data)
{
	int			*fd;
	t_cmd	*tmp;

	tmp = data->command;
	while (tmp)
	{
		if (tmp->pipe_out || (tmp->prev && tmp->prev->pipe_out))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_shell(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}