/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:01:59 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 13:41:50 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fix_path_if_going_home(t_shell **shell)
{
	char	**cmd;
	char	*tmp;
	char	*home;

	cmd = (*shell)->cmd;
	while (*cmd)
	{
		if (*cmd[0] == '~')
		{
			tmp = *cmd;
			home = get_env_val(shell, "HOME");
			*cmd = ft_strjoin(home, (*cmd + 1));
			ft_strdel(&tmp);
			if (!home)
			{
				ft_putendl_fd("error: no HOME env variable set", 2);
				return (-1);
			}
		}
		cmd++;
	}
	return (0);
}

void	set_env_var(t_shell **shell)
{
	char	*rdr;

	if ((rdr = ft_strnew(BUFF_SIZE)))
	{
		do_setenv(shell, "PWD", getcwd(rdr, BUFF_SIZE));
		ft_strdel(&rdr);
	}
}

int		builtin_cd(t_shell **shell)
{
	if (!(get_env_val(shell, "PWD")))
		set_env_var(shell);
	if ((prep_and_change(shell) == -1))
		return (-1);
	rebuild_str2env(shell);
	return (0);
}
