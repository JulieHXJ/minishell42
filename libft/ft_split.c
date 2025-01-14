/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:41:45 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/13 22:34:44 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(const char *s, char c)
{
	int	n;
	int	sign;

	n = 0;
	sign = 0;
	while (*s)
	{
		if (*s != c && sign != 1)
		{
			n++;
			sign = 1;
		}
		else if (*s == c)
			sign = 0;
		s++;
	}
	return (n);
}

static int	find_c(const char *s, char c, size_t *start)
{
	size_t	i;

	i = *start;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	*make_str(const char *s, size_t start, size_t cut)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start >= cut)
		return (NULL);
	str = malloc(sizeof(char) * (cut - start + 1));
	if (!str)
		return (NULL);
	while (start < cut)
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

static char	**arr_free(char **arr, size_t i_arr)
{
	while (i_arr-- > 0)
		free(arr[i_arr]);
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	start;
	size_t	i_arr;
	size_t	cut;

	start = 0;
	i_arr = 0;
	cut = 0;
	arr = malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (!s || !arr)
		return (NULL);
	while (start < ft_strlen(s))
	{
		while (s[start] == c && c != '\0')
			start++;
		if (s[start] == '\0' )
			return (arr[i_arr] = NULL, arr);
		cut = find_c(s, c, &start);
		arr[i_arr] = make_str(s, start, cut);
		if (!arr[i_arr])
			return (arr_free(arr, i_arr));
		i_arr++;
		start = cut + 1;
	}
	return (arr[i_arr] = NULL, arr);
}
