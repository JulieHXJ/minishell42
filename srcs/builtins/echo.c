/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:54:29 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 17:51:59 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *argv)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	if (argv[i] != '-')
		return (flag);
	i++;
	while (argv[i] && argv[i] == 'n')
		i++;
	if (argv[i] == '\0')
		flag = true;
	return (flag);
}

static void	print_args(char **args, bool flag, int i)
{
	if (!args[i])
	{
		if (!flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	echo_cmd(t_shell *data, char **argv)
{
	int		i;
	bool	flag;

	(void)data;
	flag = false;
	i = 1;
	while (argv[i] && is_flag(argv[i]))
	{
		flag = true;
		i++;
	}
	print_args(argv, flag, i);
	return (EXIT_SUCCESS);
}
