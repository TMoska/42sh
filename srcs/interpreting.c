/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/02/19 22:30:01 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_executable(t_shell **shell)
{
	char 	*tmp;
	char 	**paths;
	int 	paths_count;
	int 	i;

	i = 0;
	if (access((*shell)->cmd[0], F_OK) == 0)
		return ((*shell)->cmd[0]);
	tmp = get_env_val((*shell)->env_list, "PATH");
	paths = ft_strsplit(tmp, ':');
	paths_count = ft_str2len(paths);
	while (i < paths_count)
	{
		tmp = ft_str3join(paths[i], "/", (*shell)->cmd[0]);
		if (access(tmp, F_OK) == 0)
		{
			ft_str2del(paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	ft_str2del(paths);
	return (NULL);
}

static void	execute(t_shell **shell, char *exec)
{
	pid_t	pid;
	int		status;
	char	**ptr;

	pid = fork();
	ptr = (*shell)->cmd;
	if (pid == 0)
		execve(exec, ptr, (*shell)->env);
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			(*shell)->ret = WEXITSTATUS(status);
	}
}

static void	fork_and_execute(t_shell **shell, char *exec)
{
	struct stat	st;

	if (stat(exec, &st) != -1)
	{
		if ((access(exec, X_OK) != 0))
			permission_denied(shell);
		if (S_ISREG(st.st_mode) && st.st_mode)
			execute(shell, exec);
	}
}

void		interpret_line(t_shell **shell)
{
	char	*exec;

	exec = NULL;
	if (try_a_builtin(shell))
		return ;
	else if ((exec = get_full_executable(shell)))
	{
		fork_and_execute(shell, exec);
		ft_strdel(&exec);
	}
	else
		command_not_found(shell);
}
