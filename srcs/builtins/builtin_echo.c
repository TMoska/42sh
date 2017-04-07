/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/06 00:53:06 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(t_shell **shell)
{
	int		i;

	i = 1;
	if (ft_strcmp((*shell)->cmd[1], "-n") == 0)
		++i;
	while ((*shell)->cmd[i])
	{
		ft_putstr((*shell)->cmd[i]);
		++i;
		((*shell)->cmd[i]) ? ft_putchar(' ') : (0);
	}
	if (ft_strcmp((*shell)->cmd[1], "-n") != 0)
		ft_putchar('\n');
	return (0);
}
