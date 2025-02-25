/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:26:06 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/25 12:05:50 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_key_value(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(*tmp) * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

static void	sort_var(char **envp)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	len = count_env(envp);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(t_shell *data)
{
	int	i;

	if (!data->envp)
		return (1);
	sort_var(data->envp);
	i = 0;
	while (data->envp[i])
	{
		printf("declare -x ");
		print_value(data->envp[i]);
		i++;
	}
	return (0);
}

int	export_builtin(t_shell *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = 0;
	i = 1;
	if (!args[i])
		return (print_export(data));
	while (args[i])
	{
		if (!valid_envp(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value(args[i]);
			set_envp_var(data, tmp[0], tmp[1]);
			free_arr(tmp);
		}
		i++;
	}
	return (ret);
}
