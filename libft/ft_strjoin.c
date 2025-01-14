/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:15:00 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/16 15:36:05 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
		return (NULL);
	if (len1 != 0)
		ft_memcpy(new, s1, len1);
	if (len2 != 0)
		ft_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	return (new);
}
