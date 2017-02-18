/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 22:32:02 by moska             #+#    #+#             */
/*   Updated: 2017/02/18 23:03:33 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_is_good(char *cmd)
{
	// Todo: syntax checking
	if (!cmd || ft_strisblank(cmd))
		return (0);
	return (1);
}

int			validate_and_prep_cmd(t_shell **shell)
{
	if (command_is_good((*shell)->buff))
	{
		(*shell)->buff = ft_strtrim((*shell)->buff);
		return (1);
	}
	return (0);
}
