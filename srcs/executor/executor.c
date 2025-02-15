/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:16:11 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/15 15:41:59 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_last_exit_code;

int	execute_command(t_shell *data, t_cmd *cmd)
{
	int	ret;

	if (!cmd || !cmd->cmd)
		terminate_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io))
		terminate_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd_lst, cmd);
	re_pipe(cmd->io);
	close_fds(data->cmd_lst, false);
	if (ft_strchr(cmd->cmd, '/') == NULL)
	{
		ret = execute_builtin(data, cmd);
		if (ret != 127)
			terminate_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != 127)
			terminate_shell(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	terminate_shell(data, ret);
	return (ret);
}

static int	get_children(t_shell *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd_lst, false);
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

	cmd = data->cmd_lst;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int	prep_for_exec(t_shell *data)
{
	if (!data || !data->cmd_lst)
		return (EXIT_SUCCESS);
	if (!data->cmd_lst->cmd)
	{
		if (data->cmd_lst->io && !check_infile_outfile(data->cmd_lst->io))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (127);
}

int	execute(t_shell *data)
{
	int		ret;
	t_cmd	*cmd;

	cmd = data->cmd_lst;
	ret = prep_for_exec(data);
	if (ret != 127)
		return (ret);
	if (!data->cmd_lst->if_pipe && !data->cmd_lst->prev
		&& check_infile_outfile(data->cmd_lst->io))
	{
		re_pipe(data->cmd_lst->io);
		ret = execute_builtin(data, data->cmd_lst);
		restore_io(data->cmd_lst->io);
	}
	if (ret != 127)
		return (ret);
	return (create_children(data));
}
