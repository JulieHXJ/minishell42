/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:20:36 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/13 13:27:53 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*there;
	char	cc;

	i = 0;
	there = NULL;
	cc = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			there = (char *)&s[i];
		i++;
	}
	if (cc == '\0')
		return ((char *)s + i);
	return (there);
}
