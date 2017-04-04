/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 21:17:52 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/04 05:58:59 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_executable(t_shell **shell, char *exec, char *path)
{
	char	*tmp;
	char	**paths;
	int		i;
	char	*cmd;

	cmd = ((exec) ? exec : (*shell)->cmd[0]);
	i = 0;
	paths = ft_strsplit(path, ':');
	if ((tmp = loop_through_paths(&paths, &i, cmd)))
	{
		ft_str2del(&paths);
		return (tmp);
	}
	if (access(cmd, F_OK) == 0)
	{
		ft_str2del(&paths);
		return (ft_strdup(cmd));
	}
	ft_str2del(&paths);
	return (NULL);
}

static int	fork_and_execute(t_shell **shell, char *exec)
{
	struct stat	st;
	int			ret;

	ret = -1;
	if (stat(exec, &st) != -1)
	{
		if ((access(exec, X_OK) != 0))
			ret = permission_denied(shell, TRUE, NULL);
		else if (S_ISREG(st.st_mode) && st.st_mode)
			ret = 0;
	}
	return (ret);
}

int			get_and_test_executable(t_shell **shell, char **exec, char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = get_env_val_2str(env, "PATH");
	if ((*exec = get_full_executable(shell, *exec, path)))
		return (fork_and_execute(shell, *exec));
	else
		return (command_not_found(shell));
}
