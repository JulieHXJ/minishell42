/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:12:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:58:39 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delete_var(t_token **token_node, char *str, int n)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + n);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == n)
		{
			i = i + var_length(str + n) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr((*token_node)->input);
	(*token_node)->input = new_str;
	return (0);
}

static char	*delete_and_replace(t_token **token_node, char *str,
			char *var_value, int n)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - var_length(str + n)
			+ ft_strlen(var_value));
	newstr = replace_token(str, var_value, newstr_size, n);
	if (token_node && *token_node)
	{
		free_ptr((*token_node)->input);
		(*token_node)->input = newstr;
	}
	return (newstr);
}

int	replace_var(t_token **token_node, char *var_value, int n)
{
	if (var_value == NULL)
	{
		if (delete_var(token_node, (*token_node)->input, n) == 1)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	else
	{
		if (delete_and_replace(token_node, (*token_node)->input, \
		var_value, n) == NULL)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	free_ptr(var_value);
	return (0);
}

char	*replace_val_hd(char *str, char *var_value, int n)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = delete_and_replace(NULL, str, var_value, n);
		free_ptr(tmp);
	}
	free_ptr(var_value);
	return (str);
}
