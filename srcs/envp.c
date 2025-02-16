/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:29:17 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/16 17:59:03 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	get_envp_index(char **env, char *var)
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
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

char	*get_envp_value(char *str, char **envp)
{
	int		i;
	int		len;
	char	*temp;

	if (!str || !envp)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
		{
			temp = ft_strdup(envp[i] + len + 1);
			if (!temp)
				return (NULL);
			return (temp);
		}
		i++;
	}
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

bool	set_envp_var(t_shell *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_envp_index(data->envp, key);
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
		idx = count_env(data->envp);
		data->envp = realloc_env_vars(data, idx + 1);
		if (!data->envp)
			return (false);
		data->envp[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}
