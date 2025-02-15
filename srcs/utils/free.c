/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:30:23 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/13 21:39:50 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free_ptr(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_shell(t_shell *minishell, bool free_all)
{
	if (minishell && minishell->input)
	{
		free_ptr(minishell->input);
	}
	if (minishell && minishell->token_lst)
		free_token(&minishell->token_lst, &free_ptr);
	if (minishell && minishell->cmd_lst)
		free_cmd(&minishell->cmd_lst, &free_ptr);
	if (free_all == true)
	{
		if (minishell && minishell->cur_dir)
			free_ptr(minishell->cur_dir);
		if (minishell && minishell->old_dir)
			free_ptr(minishell->old_dir);
		if (minishell && minishell->envp)
			free_arr(minishell->envp);
		rl_clear_history();
	}
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->io)
	{
		if (cmds->io->fd_in != -1)
			close(cmds->io->fd_in);
		if (cmds->io->fd_out != -1)
			close(cmds->io->fd_out);
		if (close_backups)
			restore_io(cmds->io);
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_redir *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}
