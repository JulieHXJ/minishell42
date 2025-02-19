/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:16:11 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/19 16:35:38 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_code;

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

int	execute_builtin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = 127;
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		ret = cd_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		ret = echo_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		ret = env_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ret = export_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		ret = pwd_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		ret = unset_builtin(data, cmd->args_list);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ret = exit_builtin(data, cmd->args_list);
	return (ret);
}

int	executor(t_shell *data)
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
