/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 23:32:19 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 20:57:40 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_int(char *cmd)
{
	while (*cmd)
	{
		if (!ft_isdigit(*cmd))
			return (0);
		cmd++;
	}
	return (1);
}

static void	manage_return_code(t_shell **shell)
{
	int arg;

	if (!is_all_int((*shell)->cmd[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		(*shell)->ret = 2;
		g_exit_code = 2;
	}
	else if ((arg = ft_atoi((*shell)->cmd[1])))
	{
		(*shell)->ret = arg;
		g_exit_code = arg;
	}
}

void		builtin_exit(t_shell **shell)
{
	if ((*shell)->cmd_len > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	else if ((*shell)->cmd_len == 2)
		manage_return_code(shell);
	mid_clean_shell(shell);
	clean_shell(shell);
	exit((*shell)->ret);
}
