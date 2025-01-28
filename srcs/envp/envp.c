/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:29:17 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/28 16:35:00 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	envp_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

char	*envp_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

char	**realloc_env_vars(t_shell *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->envp[i] && i < size)
	{
		new_env[i] = ft_strdup(data->envp[i]);
		free_ptr(data->envp[i]);
		i++;
	}
	free(data->envp);
	return (new_env);
}

bool	set_env_var(t_shell *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = envp_index(data->envp, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->envp[idx])
	{
		free_ptr(data->envp[idx]);
		data->envp[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = envp_count(data->envp);
		data->envp = realloc_env_vars(data, idx + 1);
		if (!data->envp)
			return (false);
		data->envp[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}
