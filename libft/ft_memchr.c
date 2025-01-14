/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:26:25 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/09 17:27:30 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	check;

	str = (unsigned char *)s;
	check = (unsigned char)c;
	while (n--)
	{
		if (*str == check)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
