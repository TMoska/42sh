/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/04 17:00:30 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	construct_command(t_shell **shell)
{
	char	**tmp;
	char	**random;
	char	**ret;
	int		i;

	i = 0;
	tmp = ft_strsplit((*shell)->buff, ';');
	random = ft_str2new(3);
	random[0] = ft_strdup("ls");
	random[1] = ft_strdup("cd");
	random[2] = ft_strdup("lala");
	ret = ft_arr_inner_join(tmp, random);
	while (*ret)
	{
		printf("> %s\n", *ret);
		ret++;
	}
	hist_add(&(*shell)->history, (*shell)->buff);
	while (tmp[i])
	{
		ft_lstadd_back(&(*shell)->commands, ft_lstnew(tmp[i],\
			ft_strlen(tmp[i]) + 1));
		// printf("+\n");
		i++;
	}
	ft_str2del(&tmp);
}
