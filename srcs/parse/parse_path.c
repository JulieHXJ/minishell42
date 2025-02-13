/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:44:09 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:52:09 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			// errmsg_cmd("malloc", NULL,
			// 	"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	**get_envp(t_shell *data)
{
	char	**env_paths;

	if (get_envp_index(data->envp, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_envp_value("PATH", data->envp), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

char	*get_cmd_path(t_shell *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_envp(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_arr(env_paths);
		return (NULL);
	}
	cmd_path = find_path(cmd, env_paths);
	if (!cmd_path)
	{
		free(cmd);
		free_arr(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
