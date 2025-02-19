/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:39:34 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/19 18:09:39 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	check_infile_outfile(t_redir *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

bool	restore_io(t_redir *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}
