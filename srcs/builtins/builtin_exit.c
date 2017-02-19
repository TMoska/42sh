/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 23:32:19 by moska             #+#    #+#             */
/*   Updated: 2017/02/19 17:33:06 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_return_code(t_shell **shell)
{
	int arg;

	if ((arg = ft_atoi((*shell)->cmd[1])))
	{
		(*shell)->ret = arg;
		if ((*shell)->cmd_len > 2)
			ft_putstr_fd("exit: too many arguments\n", 2);
	}
	// Todo: non numeric argument errors
}

void		builtin_exit(t_shell **shell)
{
	if ((*shell)->cmd_len > 1)
		manage_return_code(shell);
	(*shell)->exit = 1;
}
