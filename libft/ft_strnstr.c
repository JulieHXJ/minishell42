/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:19:08 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/13 13:48:32 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i_hay;
	size_t	nee_len;

	nee_len = ft_strlen(needle);
	i_hay = 0;
	if (*needle == '\0')
		return ((char *)(haystack));
	while (haystack[i_hay] && len > i_hay)
	{
		if (len - i_hay < nee_len)
			return (NULL);
		if (haystack[i_hay] == needle[0]
			&& ft_strncmp(&haystack[i_hay], needle, nee_len) == 0)
		{
			return ((char *)(&haystack[i_hay]));
		}
		i_hay++;
	}
	return (NULL);
}
