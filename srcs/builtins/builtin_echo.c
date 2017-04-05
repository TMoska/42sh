/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 02:54:30 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(char *cmd)
{
	int		i;
	char	**array;
	char	*tmp;

	array = ft_splitquotes(cmd, ' ');
	i = 1;
	if (ft_strcmp(array[1], "-n") == 0)
		++i;
	while (array[i])
	{
		tmp = treat_quotes(array[i]);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		++i;
		(array[i]) ? ft_putchar(' ') : (0);
	}
	if (ft_strcmp(array[1], "-n") != 0)
		ft_putchar('\n');
	ft_str2del(&array);
	return (0);
}
