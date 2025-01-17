/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:28:55 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/17 16:35:09 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_check(t_shell *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*search_var_envp(t_shell *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->envp[i] + len);
	return (str);
}

char	*retrieve_var(t_token *token, char *str, t_shell *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_check(data, var) == 0)
	{
		if (token != NULL)
			token->var_check = true;
		value = search_var_envp(data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(global_exit_code);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
