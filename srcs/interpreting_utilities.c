/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:52:25 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 17:49:49 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loop_through_paths(char ***paths, int *i, char *cmd)
{
	char	*tmp;
	int		paths_count;

	paths_count = (int)ft_str2len(*paths);
	while (*i < paths_count)
	{
		if (*i == 0)
			tmp = ft_str3join((*paths)[*i] + 5, "/", cmd);
		else
			tmp = ft_str3join((*paths)[*i], "/", cmd);
		if (access(tmp, F_OK) == 0)
		{
			ft_str2del(paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		(*i)++;
	}
	return (0);
}
