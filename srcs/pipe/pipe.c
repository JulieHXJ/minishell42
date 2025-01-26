/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:39:34 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/26 14:49:09 by xhuang           ###   ########.fr       */
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

void	init_io(t_cmd *cmd)
{
	if (!cmd->pipe)
	{
		cmd->pipe = malloc(sizeof * cmd->pipe);
		if (!cmd->pipe)
			return ;
		cmd->pipe->infile = NULL;
		cmd->pipe->outfile = NULL;
		cmd->pipe->heredoc_delimiter = NULL;
		cmd->pipe->heredoc_quotes = false;
		cmd->pipe->fd_in = -1;
		cmd->pipe->fd_out = -1;
		cmd->pipe->stdin_backup = -1;
		cmd->pipe->stdout_backup = -1;
	}
}
