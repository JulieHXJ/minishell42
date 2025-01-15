/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:18:36 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/15 16:53:58 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_envp(t_shell *data, char **envp)
{
	int		i;

	data->envp = ft_calloc(envp_count(envp) + 1, sizeof * data->envp);
	if (!data->envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	init_dir(t_shell *data)
{
	char	buff[PATH_MAX];
	char	*dir;

	dir = getcwd(buff, PATH_MAX);
	data->cur_dir = ft_strdup(dir);
	if (!data->cur_dir)
		return (false);
	if (envp_index(data->envp, "OLDPWD") != -1)
	{
		data->old_dir = ft_strdup(envp_value(data->envp, "OLDPWD"));
		if (!data->old_dir)
			return (false);
	}
	else
	{
		data->old_dir = ft_strdup(dir);
		if (!data->old_dir)
			return (false);
	}
	return (true);
}

bool	init_shell(t_shell *data, char **envp)
{
	if (!init_envp(data, envp))
	{
		ft_printf("Could not initialize envp\n");
		return (false);
	}
	if (!init_dir(data))
	{
		ft_printf("Could not initialize current working directory\n");
		return (false);
	}
	data->token = NULL;
	data->input = NULL;
	data->command = NULL;
	data->pid = -1;
	global_exit_code = 0;
	return (true);
}
