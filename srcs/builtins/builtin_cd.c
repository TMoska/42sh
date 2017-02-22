/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 22:01:59 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/22 23:11:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_var(t_shell **shell)
{
	char	*rdr;

	if ((rdr = (char*)malloc(sizeof(char) * BUFF_SIZE)))
	{
		do_setenv(shell, "PWD", getcwd(rdr, BUFF_SIZE));
		free(rdr);
	}
}

void	fix_path_if_going_home(t_shell **shell)
{
	char	**cmd;

	cmd = (*shell)->cmd;
	while (*cmd)
	{
		if (*cmd[0] == '~')
			*cmd = ft_strjoin(get_env_val(shell, "HOME"), (*cmd + 1));
		cmd++;
	}
}

void	change_directory(t_shell **shell, char *path)
{
	int		ret;
	char	*rdr;
	char	*tmp_pwd;

	if ((rdr = (char *)malloc(sizeof(char) * BUFF_SIZE)))
	{
		tmp_pwd = get_env_val(shell, "PWD");
		if (!(ret = chdir(path)))
		{
			do_setenv(shell, "OLDPWD", tmp_pwd);
			do_setenv(shell, "PWD", getcwd(rdr, BUFF_SIZE));
			(*shell)->ret = ret;
			g_exit_code = ret;
		}
		else
			permission_denied(shell, path);
		free(rdr);
	}
}

void	prep_and_change(t_shell **shell)
{
	struct stat	*stats;
	char		*path;

	path = (*shell)->cmd[1];
	if ((stats = (struct stat *)malloc(sizeof(struct stat))))
	{
		if (lstat(path, stats) == 0)
		{
			if (S_ISLNK(stats->st_mode))
			{
				// Todo: handle symlinks
			}
			else
				change_directory(shell, path);
		}
		else
			no_file_or_dir(shell);
	}
}

void	builtin_cd(t_shell **shell)
{
	if (!(get_env_val(shell, "PWD")))
		set_env_var(shell);
	fix_path_if_going_home(shell);
	// Todo: check for logal inputs
	prep_and_change(shell);
}
