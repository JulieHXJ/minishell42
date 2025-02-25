/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:29:32 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/25 12:06:26 by amesmar          ###   ########.fr       */
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

static int	execute_local_bin(t_shell *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->cmd, '/') == NULL && get_envp_index(data->envp,
			"PATH") != -1)
		return (127);
	if (access(cmd->cmd, F_OK) != 0)
	{
		errmsg_cmd(cmd->cmd, NULL, "No such file or directory", 127);
		return (127);
	}
	if (cmd_is_dir(cmd->cmd))
	{
		errmsg_cmd(cmd->cmd, NULL, "is a directory", 126);
		return (126);
	}
	if (access(cmd->cmd, F_OK | X_OK) != 0)
	{
		errmsg_cmd(cmd->cmd, NULL, "Permission denied", 126);
		return (126);
	}
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
	{
		errmsg_cmd(cmd->cmd, NULL, "command not found", 127);
		return (127);
	}
	if (execve(cmd->cmd_path, cmd->args_list, data->envp) == -1)
		return (errno);
	return (EXIT_FAILURE);
}

static void	if_cmd_empty(t_shell *data, t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
	{
		if (cmd && cmd->args_list && cmd->args_list[1])
		{
			if (cmd->cmd)
				free(cmd->cmd);
			cmd->cmd = ft_strdup(cmd->args_list[1]);
			i = 1;
			while (cmd->args_list[i])
			{
				cmd->args_list[i - 1] = cmd->args_list[i];
				i++;
			}
			cmd->args_list[i - 1] = NULL;
			execute_command(data, cmd);
			return ;
		}
		terminate_shell(data, EXIT_SUCCESS);
	}
}

int	execute_command(t_shell *data, t_cmd *cmd)
{
	int	ret;

	if (cmd && cmd->io && !check_infile_outfile(cmd->io, true))
		terminate_shell(data, EXIT_FAILURE);
	if_cmd_empty(data, cmd);
	set_pipe_fds(data->cmd_lst, cmd);
	if (!re_pipe(cmd->io))
		terminate_shell(data, EXIT_FAILURE);
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
