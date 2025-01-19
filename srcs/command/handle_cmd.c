/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:34:22 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/19 21:55:17 by amesmar          ###   ########.fr       */
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

void	handle_commands(t_shell *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
		{
			add_back_cmd(&data->command, new_cmd(false));
		}
		if (temp->type == WORD || temp->type == VAR)
		{
			parse_str(&data->command, &temp, data);
		}
		else if (temp->type == REDIRECT_IN)
			printf("REDIRECT_IN\n");
		else if (temp->type == REDIRECT_OUT)
			printf("REDIRECT_OUT\n");
		else if (temp->type == HEREDOC)
			printf("HEREDOC\n");
		else if (temp->type == APPEND)
			printf("APPEND\n");
		else if (temp->type == PIPE)
			printf("PIPE\n");
		else if (temp->type == END)
			break ;
	}
	no_arg(data);
}
