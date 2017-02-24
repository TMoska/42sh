/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:01:59 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/24 17:17:15 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_path_if_going_home(t_shell **shell)
{
	char	**cmd;
	char	*tmp;

	cmd = (*shell)->cmd;
	while (*cmd)
	{
		if (*cmd[0] == '~')
		{
			tmp = *cmd;
			*cmd = ft_strjoin(get_env_val(shell, "HOME"), (*cmd + 1));
			ft_strdel(&tmp);
		}
		cmd++;
	}
}

void	set_env_var(t_shell **shell)
{
	char	*rdr;

	if ((rdr = (char*)malloc(sizeof(char) * BUFF_SIZE)))
	{
		do_setenv(shell, "PWD", getcwd(rdr, BUFF_SIZE));
		free(rdr);
	}
}

void	builtin_cd(t_shell **shell)
{
	if (!(get_env_val(shell, "PWD")))
		set_env_var(shell);
	fix_path_if_going_home(shell);
	prep_and_change(shell);
	rebuild_str2env(shell);
}
