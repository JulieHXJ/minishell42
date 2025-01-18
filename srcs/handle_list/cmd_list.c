/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:45:24 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 18:01:34 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(bool value)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	new_node->pipe_out = value;
	cmd_init(&new_node);
	return (new_node);
}

void	add_back_cmd(t_cmd **alst, t_cmd *new_node)
{
	t_cmd	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	delone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->arg)
		free_array(lst->arg);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->pipe)
		free_io(lst->pipe);
	(*del)(lst);
}

void	clear_cmd(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		delone_cmd(*lst, del);
		*lst = temp;
	}
}
