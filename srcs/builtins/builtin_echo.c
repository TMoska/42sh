/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 05:48:27 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(char *cmd)
{
	int		i;
	char	**array;

	i = 1;
	array = ft_splittreat(cmd, ' ');
	if (ft_strcmp(array[1], "-n") == 0)
		++i;
	while (array[i])
	{
		ft_putstr(array[i]);
		++i;
		(array[i]) ? ft_putchar(' ') : (0);
	}
	if (ft_strcmp(array[1], "-n") != 0)
		ft_putchar('\n');
	ft_str2del(&array);
	return (0);
}
