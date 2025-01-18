/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:26:14 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 17:49:42 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static int	create_args(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb = count_args(temp);
	last_cmd->arg = malloc(sizeof(char *) * (nb + 2));
	if (!last_cmd->arg)
		return (1);
	temp = *token_node;
	i = 0;
	last_cmd->arg[i] = ft_strdup(last_cmd->cmd);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd->arg[i] = ft_strdup(temp->input);
		i++;
		temp = temp->next;
	}
	last_cmd->arg[i] = NULL;
	*token_node = temp;
	return (0);
}

static char	**copy_args(int len, char **arr, t_cmd *cmd, t_token **node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *node;
	while (i < len)
	{
		arr[i] = cmd->arg[i];
		i++;
	}
	while (temp->type == WORD || temp->type == VAR)
	{
		arr[i] = ft_strdup(temp->input);
		i++;
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	add_args(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->arg[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (1);
	new_tab = copy_args(len, new_tab, last_cmd, token_node);
	free(last_cmd->arg);
	last_cmd->arg = new_tab;
	*token_node = temp;
	return (0);
}

int	handle_args(t_token **token_node, t_cmd *last_cmd)
{
	if (!ft_strcmp(last_cmd->cmd, "echo"))
	{
		if (!(last_cmd->arg))
			return (create_args_echo(token_node, last_cmd));
		else
			return (add_args_echo(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->arg))
			return (create_args(token_node, last_cmd));
		else
			return (add_args(token_node, last_cmd));
	}
	return (0);
}
