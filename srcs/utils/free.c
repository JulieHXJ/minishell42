/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:30:23 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/19 21:47:57 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_array(char **arr)
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
		minishell->input = NULL;
	}
    /////// to do ////////
	if (minishell && minishell->token)
		clear_token(&minishell->token, &free_ptr);
	if (minishell && minishell->command)
		clear_cmd(&minishell->command, &free_ptr);
	if (free_all == true)
	{
		if (minishell && minishell->cur_dir)
			free_ptr(minishell->cur_dir);
		if (minishell && minishell->old_dir)
			free_ptr(minishell->old_dir);
		if (minishell && minishell->envp)
			free_array(minishell->envp);
		rl_clear_history();
	}
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->pipe)
	{
		if (cmds->pipe->fd_in != -1)
			close(cmds->pipe->fd_in);
		if (cmds->pipe->fd_out != -1)
			close(cmds->pipe->fd_out);
		if (close_backups)
			re_pipe(cmds->pipe);
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_pipe *io)
{
	if (!io)
		return ;
	re_pipe(io);
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
