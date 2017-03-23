/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 22:32:02 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 21:06:39 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_is_good(char *cmd)
{
	if (!cmd || ft_strisblank(cmd))
		return (0);
	return (1);
}

int			validate_and_prep_cmd(t_shell **shell)
{
	char *tmp;

	if (command_is_good((*shell)->buff))
	{
		tmp = (*shell)->buff;
		(*shell)->buff = ft_strtrim((*shell)->buff);
		free(tmp);
		return (1);
	}
	return (0);
}
