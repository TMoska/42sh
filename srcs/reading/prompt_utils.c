/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:54:38 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 23:35:39 by ede-sous         ###   ########.fr       */
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
	char	*home;

	git = get_git_branch();
	path = getcwd(NULL, 0);
	home = get_env_val(shell, "HOME");
	if (home && home[0] != '\0' && ft_strstr(path, home))
		ft_str_replace(&path, home, "~", 1);
	ft_putstr("\033[0;35m");
	if ((logname = get_env_val(shell, "LOGNAME")))
	{
		ft_putstr(logname);
		ft_putstr("\033[0;33m:");
	}
	ft_putstr("\033[0;32m");
	ft_putstr(path);
	if (git)
	{
		ft_putstr("\033[0;33m:\033[0;36m");
		ft_putstr(git);
		ft_strdel(&git);
	}
	ft_strdel(&path);
}
