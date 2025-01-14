/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:29:34 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/09 17:30:02 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!src && !dst)
		return (0);
	if (d > s)
	{
		while (n > 0)
		{
			d[n - 1] = s[n -1];
			n--;
		}
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
