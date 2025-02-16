/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:45:24 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:23:30 by xhuang           ###   ########.fr       */
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
	new_node->if_pipe = value;
	return (new_node);
}

void	add_cmd(t_cmd **cmd_lst, t_cmd *new_node)
{
	t_cmd	*start;

	start = *cmd_lst;
	if (start == NULL)
	{
		*cmd_lst = new_node;
		return ;
	}
	if (cmd_lst && *cmd_lst && new_node)
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

static void	delone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->args_list)
		free_arr(lst->args_list);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->io)
		free_io(lst->io);
	(*del)(lst);
}

void	free_cmd(t_cmd **lst, void (*del)(void *))
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
