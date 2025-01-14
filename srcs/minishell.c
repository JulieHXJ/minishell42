/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/14 18:26:05 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_function(int i)
{
	ft_printf("The integer is %d\n", i);
}

int	main(void)
{
	test_function(2);
	test_function(2);
	ft_printf("the string is %s\n", "Hello");
	return (0);
}
