/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/04 06:39:06 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*ft_setquotes(int *array, const char *s, char c)
{
	int		found;
	int		wc;
	int		i;

	i = -1;
	wc = 0;
	found = 0;
	while (s[++i])
		if (s[i] == c)
			found = 0;
		else
		{
			if ((s[i] == '`' || s[i] == '"' || s[i] == 39) && s[i - 1] != '\\')
			{
				(s[i] == '\'') ? (array[wc] = 1) : (0);
				i = ft_endquo(s, i);
			}
			(found == 0) ? wc++ : (0);
			found = 1;
		}
	return (array);
}

int		builtin_echo(char *cmd)
{
	int		i;
	char	**array;
	int		*iarray;

	array = ft_splitquotes(cmd, ' ');
	i = 1;
	iarray = ft_memalloc(sizeof(int) * (ft_str2len(array) + 1));
	iarray = ft_setquotes(iarray, (cmd + 4), ' ');
	if (ft_strcmp(array[1], "-n") == 0)
		++i;
	while (array[i])
	{
		ft_putstr(treat_quotes(array[i]));
		++i;
		(array[i]) ? ft_putchar(' ') : (0);
	}
	if (ft_strcmp(array[1], "-n") != 0)
		ft_putchar('\n');
	ft_str2del(&array);
	free(iarray);
	return (0);
}
