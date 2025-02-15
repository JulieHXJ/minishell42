/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:18:36 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/15 20:35:13 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !!!!if no envp(env -i ./minishell), PWD and SHLVL should be default
void	set_default_envp(t_shell *mini)
{
	char	buffer[PATH_MAX];
	char	*dir;

	mini->envp = malloc(3 * sizeof(char *));
	if (!mini->envp)
	{
		perror("envp allocate failed");
		exit(EXIT_FAILURE);
	}
	dir = getcwd(buffer, PATH_MAX);
	mini->envp[0] = ft_strjoin("PWD=", dir);
	if (!mini->envp[0])
	{
		perror("PWD allocation failed");
		exit(EXIT_FAILURE);
	}
	mini->envp[1] = ft_strdup("SHLVL=1");
	if (!mini->envp[1])
	{
		perror("SHLVL allocation failed");
		exit(EXIT_FAILURE);
	}
	mini->envp[2] = NULL;
}

// !!!!!!if SHLVL exsit, it should start from value + 1 and no greater than 999
// !!!!!!if SHLVL not exsit, add to envp from one
void	handle_shlvl(t_shell *mini)
{
	char	*shlvl_value;
	int		level;
	char	*shlvl_new;

	shlvl_value = get_envp_value("SHLVL", mini->envp);
	if (!shlvl_value)
	{
		shlvl_new = ft_itoa(1);
		if (!shlvl_new)
			return ;
		set_envp_var(mini, "SHLVL", shlvl_new);
		free(shlvl_new);
		return ;
	}
	level = ft_atoi(shlvl_value) + 1;
	free(shlvl_value);
	if (level >= 1000 || level < 0)
		level = 0;
	shlvl_new = ft_itoa(level);
	if (!shlvl_new)
		return ;
	set_envp_var(mini, "SHLVL", shlvl_new);
	free(shlvl_new);
}

static void	init_envp(t_shell *mini, char **envp)
{
	int	i;

	if (!envp || !envp[0])
	{
		set_default_envp(mini);
		return ;
	}
	i = count_env(envp);
	mini->envp = malloc((i + 1) * sizeof(char *));
	if (!mini->envp)
		exit(EXIT_FAILURE);
	if (i != 0)
	{
		i = 0;
		while (envp[i])
		{
			mini->envp[i] = ft_strdup(envp[i]);
			if (!mini->envp[i])
				exit(EXIT_FAILURE);
			i++;
		}
	}
	mini->envp[i] = NULL;
	handle_shlvl(mini);
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
