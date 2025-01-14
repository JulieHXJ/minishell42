/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:32:45 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/14 16:58:17 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*put_line(char *s)
{
	char	*new;
	int		i;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	new = ft_calloc((i + 1), sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		new[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

static char	*update_buf(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	new = ft_calloc(ft_strlen(s) - i, sizeof(char));
	if (!new)
	{
		free (s);
		return (NULL);
	}
	i += 1;
	while (s[i])
		new[j++] = s[i++];
	new[j] = '\0';
	free(s);
	return (new);
}

ssize_t	read_and_join(char **buf_large, int fd)
{
	ssize_t	char_read;
	char	buf_temp[BUFFER_SIZE + 1];
	char	*str_join;

	str_join = NULL;
	char_read = read(fd, buf_temp, BUFFER_SIZE);
	if (char_read <= 0)
		return (char_read);
	buf_temp[char_read] = '\0';
	if (!*buf_large)
	{
		*buf_large = ft_calloc(1, sizeof(char));
		if (!*buf_large)
			return (-1);
	}
	str_join = *buf_large;
	*buf_large = ft_strjoin(str_join, buf_temp);
	free(str_join);
	if (!*buf_large)
		return (-1);
	return (char_read);
}

char	*get_next_line(int fd)
{
	ssize_t		char_read;
	static char	*buf = NULL;
	char		*new_line;

	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		char_read = read_and_join(&buf, fd);
		if (char_read == -1)
			return (free(buf), buf = NULL, NULL);
		if (char_read == 0 && (!buf || !my_strchr(buf, '\n')))
			return (new_line = put_line(buf), free(buf), buf = NULL, new_line);
		if (ft_strchr(buf, '\n'))
		{
			new_line = put_line(buf);
			if (!new_line)
				return (free(buf), buf = NULL, NULL);
			buf = update_buf(buf);
			if (!buf)
				return (free(new_line), new_line = NULL, NULL);
			return (new_line);
		}
	}
}
