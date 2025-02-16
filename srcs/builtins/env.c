/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:45:31 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/16 15:49:58 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_shell *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

void	print_value(char *str)
{
	while (str && *str && *str != '=')
	{
		printf("%c", *str);
		str++;
	}
	if (str && *str == '=')
	{
		printf("=\"");
		str++;
		while (str && *str)
		{
			printf("%c", *str);
			str++;
		}
		printf("\"");
	}
	printf("\n");
}

bool	valid_envp(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
