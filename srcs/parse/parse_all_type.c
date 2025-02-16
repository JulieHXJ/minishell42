/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:34:22 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:19:01 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_arg(t_shell *data)
{
	t_cmd	*temp_cmd;

	if (!data || !data->cmd_lst)
		return ;
	temp_cmd = data->cmd_lst;
	while (temp_cmd && temp_cmd->cmd)
	{
		if (!temp_cmd->args_list)
		{
			temp_cmd->args_list = malloc(sizeof * temp_cmd->args_list * 2);
			temp_cmd->args_list[0] = ft_strdup(temp_cmd->cmd);
			temp_cmd->args_list[1] = NULL;
		}
		temp_cmd = temp_cmd->next;
	}
	temp_cmd = last_cmd(data->cmd_lst);
}

void	parse_pipe(t_cmd **cmd, t_token **token_lst)
{
	t_cmd	*last_node;

	last_node = last_cmd(*cmd);
	last_node->if_pipe = true;
	add_cmd(&last_node, new_cmd(false));
	*token_lst = (*token_lst)->next;
}

void	parse_all_type(t_shell *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			add_cmd(&data->cmd_lst, new_cmd(false));
		if (temp->type == WORD || temp->type == VAR)
			parse_str(&data->cmd_lst, &temp, data);
		else if (temp->type == REDIRECT_IN)
			parse_redir_in(&data->cmd_lst, &temp);
		else if (temp->type == REDIRECT_OUT)
			parse_redir_out(&data->cmd_lst, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd_lst, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd_lst, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd_lst, &temp);
		else if (temp->type == END)
			break ;
	}
	no_arg(data);
}
