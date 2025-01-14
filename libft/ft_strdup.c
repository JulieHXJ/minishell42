/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:13:44 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/09 18:14:19 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*str;

	n = ft_strlen(s1);
	str = malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, n);
	str[n] = '\0';
	return (str);
}
