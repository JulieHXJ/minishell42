/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:58:30 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/16 17:19:35 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_token	*new_tokens;
	t_token	*tmp;
	char	**strs;
	int		i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->cmd = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		add_token(&new_tokens, new_token(ft_strdup(strs[i]), NULL, WORD,
				DEFAULT));
	add_token(&new_tokens, new_token(NULL, NULL, END, DEFAULT));
	handle_args(&new_tokens, last_cmd);
	free_token(&tmp, &free_ptr);
	free_arr(strs);
}

void	parse_str(t_cmd **cmd, t_token **token_lst, t_shell *minishell)
{
	t_token	*temp;
	t_cmd	*last_command;

	(void)minishell;
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
