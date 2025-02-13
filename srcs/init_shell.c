/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:18:36 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/13 20:17:30 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool	init_envp(t_shell *data, char **envp)
// {
// 	int		i;

// 	data->envp = ft_calloc(envp_count(envp) + 1, sizeof * data->envp);
// 	if (!data->envp)
// 		return (false);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		data->envp[i] = ft_strdup(envp[i]);
// 		if (!data->envp[i])
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// static bool	init_dir(t_shell *data)
// {
// 	char	buff[PATH_MAX];
// 	char	*dir;

// 	dir = getcwd(buff, PATH_MAX);
// 	data->cur_dir = ft_strdup(dir);
// 	if (!data->cur_dir)
// 		return (false);
// 	if (envp_index(data->envp, "OLDPWD") != -1)
// 	{
// 		data->old_dir = ft_strdup(envp_value(data->envp, "OLDPWD"));
// 		if (!data->old_dir)
// 			return (false);
// 	}
// 	else
// 	{
// 		data->old_dir = ft_strdup(dir);
// 		if (!data->old_dir)
// 			return (false);
// 	}
// 	return (true);
// }

// bool	init_shell(t_shell *data, char **envp)
// {
// 	if (!init_envp(data, envp))
// 	{
// 		ft_printf("Could not initialize envp\n");
// 		return (false);
// 	}
// 	if (!init_dir(data))
// 	{
// 		ft_printf("Could not initialize current working directory\n");
// 		return (false);
// 	}
// 	data->token = NULL;
// 	data->input = NULL;
// 	data->command = NULL;
// 	data->pid = -1;
// 	global_exit_code = 0;
// 	return (true);
// }

static void	init_envp(t_shell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	mini->envp = malloc((i + 1) * sizeof(char *));
	if (!mini->envp)
	{
		perror("envp allocate failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		mini->envp[i] = ft_strdup(envp[i]);
		if (!mini->envp[i])
		{
			perror("envp duplicate failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mini->envp[i] = NULL;
}

/**
 * @brief retrieve the current working dir to cur_dir for cmd like pwd and cd,
 * and save the previous dir to old_dir
 */
static void	init_dir(t_shell *mini)
{
	char	buffer[PATH_MAX];
	char	*dir;
	char	*value;

	dir = getcwd(buffer, PATH_MAX);
	mini->cur_dir = ft_strdup(dir);
	if (get_envp_index(mini->envp, "OLDPWD") != -1)
	{
		value = get_envp_value("OLDPWD", mini->envp);
		if (!value)
		{
			perror("get value failed");
			exit(EXIT_FAILURE);
		}
		mini->old_dir = ft_strdup(value);
		free(value);
	}
	else
		mini->old_dir = ft_strdup(dir);
	if (!mini->cur_dir || !mini->old_dir)
	{
		perror("directory initialization failed");
		exit(EXIT_FAILURE);
	}
}

bool	init_shell(t_shell *mini, char **envp)
{
	init_envp(mini, envp);
	init_dir(mini);
	mini->input = NULL;
	mini->token_lst = NULL;
	mini->cmd_lst = NULL;
	mini->pid = -1;
	global_exit_code = 0;
	return (true);
}
