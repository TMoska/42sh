/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utilities2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:10:26 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/23 22:24:33 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory(t_shell **shell, char *path)
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
		free(rdr);
	}
}

static void	handle_errors(t_shell **shell, char *path, struct stat *stats)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, R_OK) == -1)
			permission_denied(shell, path);
		else if (!S_ISDIR(stats->st_mode))
			not_a_dir(shell);
	}
	else
		no_file_or_dir(shell);
}

static void	start_moving(t_shell **shell, char *path, struct stat *stats,\
	int p_option)
{
	if (lstat(path, stats) == 0 || p_option)
	{
		if (S_ISLNK(stats->st_mode) && p_option == 0)
			change_symlink_directory(shell, path);
		else
		{
			if (p_option)
				path = (*shell)->cmd[2];
			change_directory(shell, path);
		}
	}
}

static char	*fix_path_special_cases(t_shell **shell, char *path)
{
	char		*oldpwd;

	oldpwd = NULL;
	if (!path)
		return (get_env_val(shell, "HOME"));
	else if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = get_env_val(shell, "OLDPWD");
		return (oldpwd ? oldpwd : get_env_val(shell, "HOME"));
	}
	else
		return (path);
}

void		prep_and_change(t_shell **shell)
{
	struct stat	*stats;
	char		*path;
	DIR			*opened;
	int			p_option;

	path = (*shell)->cmd[1];
	p_option = 0;
	path = fix_path_special_cases(shell, path);
	if ((stats = (struct stat *)malloc(sizeof(struct stat))))
	{
		if ((*shell)->cmd[1])
			p_option = (ft_strcmp((*shell)->cmd[1], "-P") == 0);
		if ((opened = opendir(path)) || p_option)
		{
			start_moving(shell, path, stats, p_option);
			if (opened)
				closedir(opened);
		}
		else
			handle_errors(shell, path, stats);
	}
}
