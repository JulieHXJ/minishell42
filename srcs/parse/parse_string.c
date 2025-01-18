/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:58:30 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/18 17:38:13 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static bool	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static void	split_token(t_cmd *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->cmd = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = new_tkn(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		add_back_tkn(&new_tokens, new_tkn(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	add_back_tkn(&new_tokens, new_tkn(NULL, NULL, END, DEFAULT));
	handle_args(&new_tokens, last_cmd);
	clear_tkn(&tmp, &free_ptr);
	free_array(strs);
}

void	parse_str(t_cmd **cmd, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*last_command;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_command = last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_command->cmd == NULL)
		{
			if (temp->type == VAR && check_space(temp->input))
				split_token(last_command, temp->input);
			else
				last_command->cmd = ft_strdup(temp->input);
			temp = temp->next;
		}
		else
			handle_args(&temp, last_command);
	}
	*token_lst = temp;
}
