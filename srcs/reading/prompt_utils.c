/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:54:38 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 14:46:00 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_git_branch(void)
{
	int		fd;
	char	*git;
	char	*tmp;
	int		i;

	i = 0;
	git = NULL;
	if ((fd = open(".git/HEAD", O_RDONLY)) != -1)
	{
		get_next_line(fd, &git);
		tmp = git;
		git = ft_strdup(git + 16);
		ft_strdel(&tmp);
	}
	return (git);
}

void	build_prompt(t_shell **shell)
{
	char	*git;
	char	*logname;
	char	*path;

	git = get_git_branch();
	logname = get_env_val(shell, "LOGNAME");
	path = ft_strdup(get_env_val(shell, "PWD"));
	if (ft_strcmp(get_env_val(shell, "HOME"), path) != 0)
		ft_str_replace(&path, get_env_val(shell, "HOME"), "~", 0);
	ft_putstr("\033[0;35m");
	ft_putstr(logname);
	ft_putstr("\033[0;33m:\033[0;32m");
	ft_putstr(path);
	(*shell)->term->prompt_len = ft_strlen(logname) + ft_strlen(path) + 1;
	if (git)
	{
		ft_putstr("\033[0;33m:\033[0;36m");
		ft_putstr(git);
		(*shell)->term->prompt_len += ft_strlen(git) + 1;
		ft_strdel(&git);
	}
	ft_strdel(&path);
}
