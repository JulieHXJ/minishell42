/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:48:53 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/18 19:07:42 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_infile_outfile(t_pipe *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}


void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	re_pipe(t_pipe *io)
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

bool	redirect_io(t_pipe *io)
{
	int ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
	{
		printf("dup stdin backup %s", strerror(errno));
		ret = false;
	}
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
	{
		printf("dup stdout backup %s", strerror(errno));
		ret = false;
	}
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
		{
			printf("dup2 %s %s", io->infile, strerror(errno));
			ret = false;
		}
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		{
			printf("dup2 %s %s", io->outfile, strerror(errno));
			ret = false;
		}
	return (ret);
}

 bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_out)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_out)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}
