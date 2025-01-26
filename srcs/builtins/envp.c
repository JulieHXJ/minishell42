/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:45:31 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/25 12:45:51 by amesmar          ###   ########.fr       */
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
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
