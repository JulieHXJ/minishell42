/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:16:11 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 19:12:27 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

static int	get_children(t_shell *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->command, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_children(t_shell *data)
{
	t_cmd	*cmd;

	cmd = data->command;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			//print something return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
			return EXIT_FAILURE;
		}
		else if (data->pid == 0)
			execute_cmd(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int	prep_for_exec(t_shell *data)
{
	if (!data || !data->command)
		return (EXIT_SUCCESS);
	if (!data->command->cmd)
	{
		if (data->command->pipe
			&& !check_infile_outfile(data->command->pipe))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (127); // command not found
}

int	execute(t_shell *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != 127) // command not found
		return (ret);
	if (!data->command->pipe_out && !data->command->prev
		&& check_infile_outfile(data->command->pipe))
	{
		redirect_io(data->command->pipe);
		ret = execute_cmd(data, data->command);
		re_pipe(data->command->pipe);
	}
	if (ret != 127)
		return (ret);
	return (create_children(data));
}
