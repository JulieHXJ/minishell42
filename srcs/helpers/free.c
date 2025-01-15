/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:30:23 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/15 17:06:50 by amesmar          ###   ########.fr       */
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

void	free_shell(t_shell *data, bool clear_history)
{
	if (data && data->input)
	{
		free_ptr(data->input);
		data->input = NULL;
	}
    ///////// to do ////////
	// if (data && data->token)
	// 	lstclear_token(&data->token, &free_ptr);
	// if (data && data->command)
	// 	lst_clear_cmd(&data->command, &free_ptr);
	if (clear_history == true)
	{
		if (data && data->cur_dir)
			free_ptr(data->cur_dir);
		if (data && data->old_dir)
			free_ptr(data->old_dir);
		if (data && data->envp)
			free_array(data->envp);
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
