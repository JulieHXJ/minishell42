/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:38:41 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:04:09 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_join(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->input);
	while (temp->type == VAR && temp->next->type == VAR
		&& temp->next->joined == true)
	{
		str = ft_strjoin(str, temp->next->input);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

static char	**copy_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args_list[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->joined == true)
			new_tab[i] = str_join(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->input);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		if (temp->type == VAR && temp->joined == true)
		{
			while (temp->type == VAR && temp->joined == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

int	create_args_echo(t_token **token_node, t_cmd *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	remove_empty(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	last_cmd->args_list = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args_list)
		return (1);
	i = 0;
	last_cmd->args_list[i] = ft_strdup(last_cmd->cmd);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->joined == true)
			last_cmd->args_list[i] = str_join(&temp);
		else
			last_cmd->args_list[i] = ft_strdup(temp->input);
		i++;
		temp = temp->next;
	}
	last_cmd->args_list[i] = NULL;
	*token_node = temp;
	return (0);
}

int	add_args_echo(t_token **token_node, t_cmd *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_token	*temp;

	remove_empty(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	len = 0;
	while (last_cmd->args_list[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (1);
	new_tab = copy_tab(len, new_tab, last_cmd, temp);
	free(last_cmd->args_list);
	last_cmd->args_list = new_tab;
	while (temp->type == WORD || temp->type == VAR)
		temp = temp->next;
	*token_node = temp;
	return (0);
}
