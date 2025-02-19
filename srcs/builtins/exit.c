/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:50:52 by amesmar           #+#    #+#             */
/*   Updated: 2025/02/19 17:15:34 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX) || (neg == -1 && num
			> -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (*error = true, 0);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (*error = true, 0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			return (*error = true, 0);
		i++;
	}
	i = ft_atoi_long(arg, error);
	return ((int)(i % 256));
}

static bool	check_prev_next(t_shell *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_lst;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

int	exit_builtin(t_shell *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	exist;

	exist = check_prev_next(data);
	error = false;
	if (!exist)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
		{
			ft_putendl_fd("numeric argument required", 2);
			return (terminate_shell(data, 255), 255);
		}
		else if (args[2])
		{
			ft_putendl_fd("too many arguments", 2);
			return (1);
		}
	}
	return (terminate_shell(data, exit_code), exit_code);
}
