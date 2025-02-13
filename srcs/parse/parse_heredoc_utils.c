/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:39:10 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 20:59:01 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*arr_to_str(char **arr)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (arr[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(arr[0]);
		else
		{
			str = ft_strjoin(tmp, arr[i]);
			free(tmp);
		}
		if (arr[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
	}
	free_arr(arr);
	return (str);
}

static char	*expand_line(t_shell *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_hd(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (arr_to_str(words));
}

static bool	not_delim(t_shell *data, char **line, t_redir *io, bool *ret)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*ret = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = expand_line(data, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

bool	fill_heredoc(t_shell *data, t_redir *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		preset_signals();
		line = readline(">");
		signals_during_exec();
		if (!not_delim(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}
