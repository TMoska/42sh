/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:08:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/23 22:18:46 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*join_strings_by_slash(char **split_tab, int size)
{
	char	*new;
	int		i;

	i = 0;
	size -= 1;
	new = NULL;
	while (!split_tab[i])
		i++;
	if (i > 0)
		new = ft_strjoin("/", split_tab[i]);
	if (i + 1 >= size)
		return (new);
	else
		new = (new ? (ft_str3join(new, "/", split_tab[i + 1])) :
			ft_str3join(split_tab[i], "/", split_tab[i + 1]));
	i += 2;
	while (size != 1)
	{
		if (split_tab[i])
			new = ft_str3join(new, "/", split_tab[i]);
		i++;
		size--;
	}
	ft_str2del(&split_tab);
	return (new);
}

static void		solve_dotted_path(char ***split_tab, int dots, int i)
{
	int	tmp_i;

	tmp_i = 0;
	ft_strdel(split_tab[i]);
	if (dots == 2 && i > 0)
	{
		tmp_i = i - 1;
		while (tmp_i > 0 && !*split_tab[tmp_i])
			tmp_i--;
		ft_strdel(split_tab[tmp_i]);
	}
}

static char		*deal_with_dots(char **split_tab)
{
	int	i;
	int	size;
	int	dots;

	size = ft_str2len(split_tab);
	i = 0;
	dots = 0;
	while (split_tab[i])
	{
		if (ft_strcmp(split_tab[i], ".") == 0)
			dots = 1;
		else if (ft_strcmp(split_tab[i], "..") == 0)
			dots = 2;
		if (dots)
			solve_dotted_path(&split_tab, dots, i);
		dots = 0;
		i++;
	}
	return ((size > 1) ? join_strings_by_slash(split_tab, size) : split_tab[0]);
}

static char		*get_symlink_path(char *path, char *tmp_pwd)
{
	char	*tmp;
	char	**split_tab;

	tmp = ft_str3join(tmp_pwd, "/", path);
	split_tab = ft_strsplit(tmp, '/');
	return (deal_with_dots(split_tab));
}

void			change_symlink_directory(t_shell **shell, char *path)
{
	char	*tmp_pwd;
	char	*link_path;

	tmp_pwd = get_env_val(shell, "PWD");
	link_path = NULL;
	if (ft_strstr(path, "..") || ft_strstr(path, "./"))
		link_path = get_symlink_path(path, tmp_pwd);
	if (chdir(path) == 0)
	{
		do_setenv(shell, "OLDPWD", tmp_pwd);
		(*shell)->ret = 0;
		g_exit_code = 0;
		if (path[0] == '/' && !link_path)
			do_setenv(shell, "PWD", path);
		else if (link_path)
			do_setenv(shell, "PWD", link_path);
		else
		{
			link_path = ft_str3join(tmp_pwd, "/", path);
			do_setenv(shell, "PWD", link_path);
		}
	}
	ft_strdel(&link_path);
}
