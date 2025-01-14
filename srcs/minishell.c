/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:00 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/14 19:33:03 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	minishell;

	ft_memset(&minishell, 0, sizeof(t_ms_data));
	if (check_input(&minishell, argc, argv) || init_ms())
	{
		if (minishell.interaction)
		{
			mini_interact();
		}
		else
		{
			mini_nointeract();
		}
		// terminiate(&minishell, /*global*/);
	}
	terminiate(NULL, EXIT_FAILURE);
}
