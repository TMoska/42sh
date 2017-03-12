/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:34:33 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/12 18:03:34 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_shell **shell)
{
	char	**var;
	char	**cmd;
	int		p_option;
	int		i;

	var = NULL;
	cmd = NULL;
	p_option = 0;
	i = 1;
	if ((*shell)->cmd_len == 1)
		builtin_env(shell);
	else
	{
		cmd = (*shell)->cmd;
		p_option = (ft_strcmp(cmd[1], "-p") == 0);
		i += p_option;
		while (cmd[i])
		{
			var = ft_strsplit(cmd[i], '=');
			do_setenv(shell, var[0], var[1]);
			if (p_option)
				ft_putendl(cmd[i]);
			i++;
		}
	}
}
