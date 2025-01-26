/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:58:12 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/26 15:45:39 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_relative_path(char *file_to_open)
// {
// 	char	*path;
// 	char	*ret;

// 	if (file_to_open[0] == '/')
// 		return (ft_strdup(file_to_open));
// 	path = ft_strdup("./");
// 	ret = ft_strjoin(path, file_to_open);
// 	printf("PARSING - Get_rel_path function return (: %s\n", ret);
// 	return (ret);
// }

static void	open_outfile(t_pipe *io, char *file, char *var_filename)
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
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_redir_out(t_cmd **last_node, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = last_cmd(*last_node);
	init_io(cmd);
	open_outfile(cmd->pipe, temp->next->input, temp->next->input_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
