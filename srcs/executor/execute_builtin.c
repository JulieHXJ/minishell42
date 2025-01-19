/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:29:32 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/19 21:32:19 by amesmar          ###   ########.fr       */
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

int	check_command_not_found(t_shell *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->cmd, '/') == NULL
		&& envp_index(data->envp, "PATH") != -1)
		return (127);
	if (access(cmd->cmd, F_OK) != 0)
		return (127);
	else if (cmd_is_dir(cmd->cmd))
		return (126); //non executable command
	else if (access(cmd->cmd, F_OK | X_OK) != 0)
		return (126);//non executable command
	return (EXIT_SUCCESS);
}

static int	execute_local_bin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = check_command_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->cmd, cmd->arg, data->envp) == -1)
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
	if (execve(cmd->cmd_path, cmd->arg, data->envp) == -1)
		ft_printf("Print error");
		// errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

int	execute_builtin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = 127;
	// if (ft_strncmp(cmd->command, "cd", 3) == 0)
	// 	ret = cd_builtin(data, cmd->args);
	// else 
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
	{
		ret = echo_builtin(data, cmd->arg);
	}
	// else if (ft_strncmp(cmd->command, "env", 4) == 0)
	// 	ret = env_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "export", 7) == 0)
	// 	ret = export_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
	// 	ret = pwd_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "unset", 6) == 0)
	// 	ret = unset_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "exit", 5) == 0)
	// 	ret = exit_builtin(data, cmd->args);
	return (ret);
}

int	execute_command(t_shell *data, t_cmd *cmd)
{
	printf("shell data is after eceecute : %s\n", data->input);
	int	ret;

	if (!cmd || !cmd->cmd)
		terminate_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->pipe))
		terminate_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->command, cmd);
	redirect_io(cmd->pipe);
	close_fds(data->command, false);
	if (ft_strchr(cmd->cmd, '/') == NULL)
	{
		printf("shell data is after builtin : %s\n", data->input);
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
