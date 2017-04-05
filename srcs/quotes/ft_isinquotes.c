/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 06:30:27 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/05 06:46:53 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isinquotes(char *cmd, int pos)
{
	int index;

	index = 0;
	while (index < pos)
	{
		if (ft_isquotes(cmd[index]) && cmd[index - 1] != '\\')
		{
			index = ft_endquo(cmd, index);
			if (index > pos)
				return (1);
		}
		++index;
	}
	return (0);
}
