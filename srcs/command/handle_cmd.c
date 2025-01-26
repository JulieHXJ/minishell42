/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:34:22 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/26 18:00:48 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	no_arg(t_shell *data)
{
	t_cmd	*temp_cmd;

	if (!data || !data->command)
		return ;
	temp_cmd = data->command;
	while (temp_cmd && temp_cmd->cmd)
	{
		if (!temp_cmd->arg)
		{
			temp_cmd->arg = malloc(sizeof * temp_cmd->arg * 2);
			temp_cmd->arg[0] = ft_strdup(temp_cmd->cmd);
			temp_cmd->arg[1] = NULL;
		}
		temp_cmd = temp_cmd->next;
	}
	temp_cmd = last_cmd(data->command);
}

void	parse_pipe(t_cmd **cmd, t_token **token_lst)
{
	t_cmd	*last_node;

	last_node = last_cmd(*cmd);
	last_node->pipe_out = true;
	add_back_cmd(&last_node, new_cmd(false));
	*token_lst = (*token_lst)->next;
}

void	handle_commands(t_shell *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			add_back_cmd(&data->command, new_cmd(false));
		if (temp->type == WORD || temp->type == VAR)
			parse_str(&data->command, &temp, data);
		else if (temp->type == REDIRECT_IN)
			parse_redir_in(&data->command, &temp);
		else if (temp->type == REDIRECT_OUT)
			parse_redir_out(&data->command, &temp);
		else if (temp->type == HEREDOC)
		{
			parse_heredoc(data, &data->command, &temp);
			printf("HEREDOC\n");
		}
		else if (temp->type == APPEND)
			parse_append(&data->command, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->command, &temp);
		else if (temp->type == END)
			break ;
	}
	no_arg(data);
}
