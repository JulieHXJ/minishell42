/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:45:24 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/19 21:54:26 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_init(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->cmd_path = NULL;
	(*cmd)->arg = NULL;
	(*cmd)->pipe_out = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

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
	{
		printf("CMD IS NOT NULL\n");
		cmd = cmd->next;
	}
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

void	delone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->input)
	{
		(*del)(lst->input);
		lst->input = NULL;
	}
	if (del && lst && lst->input_backup)
	{
		(*del)(lst->input_backup);
		lst->input_backup = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	clear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		delone_token(*lst, del);
		*lst = tmp;
	}
}

