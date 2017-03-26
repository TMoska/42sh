/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:54:38 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 01:09:34 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_git_branch(void)
{
	int		fd;
	char	*git;
	char	**tmp2;
	int		i;

	i = 0;
	git = NULL;
	if ((fd = open(".git/HEAD", O_RDONLY)) != -1)
	{
		get_next_line(fd, &git);
		tmp2 = ft_strsplit(git, '/');
		ft_strdel(&git);
		while (tmp2[i])
			i++;
		git = ft_strdup(tmp2[i - 1]);
		ft_str2del(&tmp2);
	}
	return (git);
}

char	*build_prompt(t_shell **shell)
{
	char	*git;
	char	*prompt;
	char	*tmp;

	git = get_git_branch();
	tmp = ft_str3join("\033[0;35m", get_env_val(shell, "LOGNAME"),\
			"\033[0;33m:\033[0;32m");
	prompt = ft_strjoin(tmp, get_env_val(shell, "PWD"));
	ft_strdel(&tmp);
	if (git)
	{
		tmp = prompt;
		prompt = ft_strjoin(prompt, "\033[0;33m:\033[0;32m");
		ft_strdel(&tmp);
		tmp = prompt;
		prompt = ft_str3join(prompt, "\033[0;36m", git);
		ft_strdel(&tmp);
		ft_strdel(&git);
	}
	return (prompt);
}
