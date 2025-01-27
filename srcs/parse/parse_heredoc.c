/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:12:26 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/27 19:56:19 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(void)
{
	char		*name;
	char		*digit;
	static int	i;

	digit = ft_itoa(i);
	if (!digit)
	{
		return (NULL);
	}
	name = ft_strjoin("/tmp/.heredoc_", digit);
	free(digit);
	i++;
	return (name);
}

static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"') || (delim[0] == '\''
			&& delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

bool	open_heredoc(t_shell *data, t_pipe *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

void	parse_heredoc(t_shell *mini, t_cmd **last_node, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;
	t_pipe	*io;

	temp = *token_lst;
	cmd = last_cmd(*last_node);
	init_io(cmd);
	io = cmd->pipe;
	if (!remove_old_fd(io, true))
		return ;
	io->infile = get_name();
	io->heredoc_delimiter = get_delim(temp->next->input, &(io->heredoc_quotes));
	if (open_heredoc(mini, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
