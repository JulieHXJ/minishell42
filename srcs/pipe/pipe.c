/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:39:34 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 21:04:21 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_pipes(t_shell *data)
{
	int			*fd;
	t_cmd	*tmp;

	tmp = data->cmd_lst;
	while (tmp)
	{
		if (tmp->if_pipe || (tmp->prev && tmp->prev->if_pipe))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_shell(data, false);
				// reset_shell(data);
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
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof * cmd->io);
		if (!cmd->io)
			return ;
		cmd->io->infile = NULL;
		cmd->io->outfile = NULL;
		cmd->io->heredoc_delimiter = NULL;
		cmd->io->heredoc_quotes = false;
		cmd->io->fd_in = -1;
		cmd->io->fd_out = -1;
		cmd->io->stdin_backup = -1;
		cmd->io->stdout_backup = -1;
	}
}
