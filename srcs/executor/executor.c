/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:18:24 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/17 19:27:02 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unfinished
int	shell_execute(t_shell *data)
{
	int	ret;

	ret = prep_for_exec(data);//todo
	if (ret != 127) // command not found
		return (ret);
	// if (!data->command->pipe_out && !data->command->prev
	// 	&& check_infile_outfile(data->command->pipe))
	{
		// redirect_io(data->command->pipe);
		ret = execute_builtin(data, data->command);//do exit
		// restore_io(data->command->pipe);
	}
	if (ret != 127)
		return (ret);
	return (create_children(data));
}


int	execute_builtin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = 127;
	// if (ft_strncmp(cmd->command, "cd", 3) == 0)
	// 	ret = cd_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "echo", 5) == 0)
	// 	ret = echo_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "env", 4) == 0)
	// 	ret = env_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "export", 7) == 0)
	// 	ret = export_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
	// 	ret = pwd_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->command, "unset", 6) == 0)
	// 	ret = unset_builtin(data, cmd->args);
	if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ret = exit_builtin(data, cmd->arg);//todo
	return (ret);
}

