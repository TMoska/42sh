/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 23:32:19 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 17:08:42 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_return_code(t_shell **shell, int cmd_len)
{
	int arg;

	if ((arg = ft_atoi((*shell)->cmd[1])))
	{
		(*shell)->ret = arg;
		if (cmd_len > 2)
			ft_putstr_fd("exit: too many arguments\n", 2);
	}
	// Todo: non numeric argument errors
}

void		builtin_exit(t_shell **shell)
{
	int   cmd_len;

	cmd_len = ft_str2len((*shell)->cmd);
	if (cmd_len > 1)
		manage_return_code(shell, cmd_len);
	(*shell)->exit = 1;
}
