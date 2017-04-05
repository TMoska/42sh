/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittreat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 05:40:47 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/05 06:29:25 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_splittreat(char *cmd, char c)
{
	char	**array;
	char	*tmp;
	int		i;

	array = ft_splitquotes(cmd, c);
	i = 0;
	while (array[i])
	{
		tmp = treat_quotes(array[i]);
		ft_strdel(&array[i]);
		array[i] = tmp;
		++i;
	}
	return (array);
}
