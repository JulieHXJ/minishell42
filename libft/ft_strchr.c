/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:12:04 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/16 15:44:18 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)(&s[ft_strlen(s)]));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(&s[i]));
		}
		i++;
	}
	return (NULL);
}
