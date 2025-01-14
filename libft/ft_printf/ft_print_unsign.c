/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:22:20 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/16 15:44:58 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	uint_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned int c)
{
	char	*str;
	int		len;

	len = uint_len(c);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	str[len] = '\0';
	if (c == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (c > 0)
	{
		str[len - 1] = c % 10 + '0';
		c = c / 10;
		len--;
	}
	return (str);
}

int	ft_putunsigned(unsigned int c)
{
	int		len;
	char	*uint;

	uint = ft_utoa(c);
	if (!uint)
		return (-1);
	if (ft_putstr(uint) == -1)
	{
		free(uint);
		return (-1);
	}
	len = str_len(uint);
	free(uint);
	return (len);
}
