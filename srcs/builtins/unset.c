/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:20:53 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/28 17:13:58 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	remove_envp(t_shell *mini, int idx)
{
	int	i;
	int	count;

	if (idx > envp_count(mini->envp))
		return (false);
	free_ptr(mini->envp[idx]);
	i = idx;
	count = idx;
	while (mini->envp[i + 1])
	{
		mini->envp[i] = ft_strdup(mini->envp[i + 1]);
		free_ptr(mini->envp[i + 1]);
		count++;
		i++;
	}
	mini->envp = realloc_env_vars(mini, count);
	if (!mini->envp)
		return (false);
	return (true);
}

int	unset_builtin(t_shell *mini, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = 0;
	i = 1;
	if (!args[i])
		return (errmsg_cmd("unset", NULL, "not enough arguments", false), 1);
	while (args[i])
	{
		if (!valid_envp(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			ret = 1;
		}
		else
		{
			idx = envp_index(mini->envp, args[i]);
			if (idx != -1)
				remove_envp(mini, idx);
		}
		i++;
	}
	return (ret);
}
