/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:21:50 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/16 15:45:11 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_convert(char input, va_list arg)
{
	if (input == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (input == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (input == 'i' || input == 'd')
		return (ft_putnbr(va_arg(arg, int)));
	else if (input == 'u')
		return (ft_putunsigned(va_arg(arg, unsigned int)));
	else if (input == 'x' || input == 'X')
		return (ft_puthex(va_arg(arg, unsigned int), input));
	else if (input == 'p')
		return (ft_putpointer(va_arg(arg, void *)));
	else if (input == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		len;
	int		cur_len;

	i = 0;
	len = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			i++;
			cur_len = ft_convert(input[i], args);
		}
		else
			cur_len = ft_putchar(input[i]);
		if (cur_len == -1)
			return (-1);
		len += cur_len;
		i++;
	}
	va_end(args);
	return (len);
}
