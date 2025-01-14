/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:49:59 by xhuang            #+#    #+#             */
/*   Updated: 2024/10/09 17:36:40 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static int	count_sign(int n)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
	}
	return (sign);
}

static char	*new_str(int n, int len, int sign)
{
	char	*str;
	long	nb;

	str = (char *)malloc(sizeof(char) * (sign + len + 1));
	nb = (long)n;
	if (!str)
		return (NULL);
	str[len + sign] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		nb = -nb;
	while (nb > 0)
	{
		str[sign + len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int	len;
	int	sign;

	len = count_len(n);
	sign = count_sign(n);
	return (new_str(n, len, sign));
}
