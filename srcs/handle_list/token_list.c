/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:05:03 by amesmar           #+#    #+#             */
/*   Updated: 2025/01/18 18:04:08 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_tkn(char *str, char *str_backup, int type, int status)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token) * 1);
	if (!(new_node))
		return (NULL);
	new_node->input = str;
	new_node->input_backup = str_backup;
	new_node->var_check = false;
	new_node->type = type;
	new_node->status = status;
	new_node->joined = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_back_tkn(t_token **alst, t_token *new_node)
{
	t_token	*start;

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

void	delone_tkn(t_token *lst, void (*del)(void *))
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

void	clear_tkn(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		delone_tkn(*lst, del);
		*lst = tmp;
	}
}

t_token	*insert_tkn(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*temp;

	temp = *head;
	if (temp == NULL)
		*head = insert;
	else if (temp == to_del)
	{
		*head = insert;
		insert->next = temp->next;
		if (temp->next != NULL)
			temp->next->prev = insert;
	}
	else
	{
		while (temp != to_del)
			temp = temp->next;
		insert->prev = temp->prev;
		temp->prev->next = insert;
		while (insert->next)
			insert = insert->next;
		temp->next->prev = insert;
		insert->next = temp->next;
	}
	free_ptr(to_del->input);
	return (free_ptr(to_del), insert);
}
