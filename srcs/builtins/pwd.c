/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:38 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/25 12:42:19 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_shell *data, char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	if (data->cur_dir)
	{
		ft_putendl_fd(data->cur_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
