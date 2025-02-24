/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:58:12 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/24 23:52:33 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_outfile(t_redir *io, char *file, char *var_filename)
{
	if (!remove_old_fd(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
}

void	parse_redir_out(t_cmd **last_node, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last_node);
	init_io(cmd);
	open_outfile(cmd->io, temp->next->input, temp->next->input_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
