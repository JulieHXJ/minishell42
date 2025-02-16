/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:29:32 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:56:55 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

static int	command_not_found(t_shell *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->cmd, '/') == NULL && get_envp_index(data->envp,
			"PATH") != -1)
		return (127);
	if (access(cmd->cmd, F_OK) != 0)
		return (127);
	else if (cmd_is_dir(cmd->cmd))
		return (126);
	else if (access(cmd->cmd, F_OK | X_OK) != 0)
		return (126);
	return (EXIT_SUCCESS);
}

//!!!!added print message
static int	execute_local_bin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = command_not_found(data, cmd);
	if (ret == 127)
		return (printf("command not found\n"), ret);
	else if (ret == 126)
		return (printf("non-executable command\n"), ret);
	if (execve(cmd->cmd, cmd->args_list, data->envp) == -1)
		return (errno);
	return (EXIT_FAILURE);
}

static int	execute_sys_bin(t_shell *data, t_cmd *cmd)
{
	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (127);
	if (cmd_is_dir(cmd->cmd))
		return (127);
	cmd->cmd_path = get_cmd_path(data, cmd->cmd);
	if (!cmd->cmd_path)
		return (127);
	if (execve(cmd->cmd_path, cmd->args_list, data->envp) == -1)
		ft_printf("Print error");
	return (EXIT_FAILURE);
}

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
