/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:22:43 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/16 15:45:07 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *c)
{
	size_t	i;

	i = 0;
	if (c == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	else
	{
		while (c[i])
		{
			if (write(1, &c[i], 1) == -1)
				return (-1);
			i++;
		}
		return (i);
	}
}

int	ft_putnbr(int c)
{
	int		len;
	char	*num;

	num = ft_itoa(c);
	if (!num)
		return (-1);
	if (ft_putstr(num) == -1)
	{
		free(num);
		return (-1);
	}
	len = str_len(num);
	free(num);
	return (len);
}

int	ft_puthex(unsigned long n, char c)
{
	char	*base;
	int		len;
	int		tem;

	len = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		return (1);
	}
	if (n >= 16)
	{
		tem = ft_puthex(n / 16, c);
		if (tem == -1)
			return (-1);
		len += tem;
	}
	if (write(1, &base[n % 16], 1) == -1)
		return (-1);
	return (len++, len);
}

int	ft_putpointer(void *ptr)
{
	int	len;
	int	n;

	len = 0;
	if (write(1, "0x", 2) == -1)
		return (-1);
	len += 2;
	if (ptr == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		len++;
	}
	else
	{
		n = ft_puthex((unsigned long)ptr, 'x');
		if (n == -1)
			return (-1);
		len += n;
	}
	return (len);
}
