/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utilities3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:37:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/24 17:38:31 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_back(char ***split_tab, char **new, int *size, int *i)
{
	char *tmp;

	tmp = NULL;
	*i += 2;
	while (*size != 1)
	{
		if (*split_tab[*i])
		{
			tmp = *new;
			*new = ft_str3join(*new, "/", *split_tab[*i]);
			ft_strdel(&tmp);
		}
		(*i)++;
		(*size)--;
	}
}
