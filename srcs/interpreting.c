/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/02/23 06:57:34 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_executable(t_shell **shell, char *exec, char *path)
{
	char	*tmp;
	char	**paths;
	int		paths_count;
	int		i;
	char	*cmd;

	cmd = ((exec) ? exec : (*shell)->cmd[0]);
	i = 0;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_strsplit(path, ':');
	paths_count = ft_str2len(paths);
	while (i < paths_count)
	{
		if (i == 0)
			tmp = ft_str3join(paths[i] + 5, "/", cmd);
		else
			tmp = ft_str3join(paths[i], "/", cmd);
		if (access(tmp, F_OK) == 0)
		{
			ft_str2del(&paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	ft_str2del(&paths);
	return (NULL);
}

static void	execute(t_shell **shell, char *exec, char **ptr, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(exec, ptr, env);
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			(*shell)->ret = WEXITSTATUS(status);
			g_exit_code = WEXITSTATUS(status);
		}
	}
}

static void	fork_and_execute(t_shell **shell, char *exec,\
		char **ptr, char **env)
{
	struct stat	st;

	if (stat(exec, &st) != -1)
	{
		if ((access(exec, X_OK) != 0))
			permission_denied(shell, NULL);
		else if (S_ISREG(st.st_mode) && st.st_mode)
			execute(shell, exec, ptr, env);
	}
}

void		must_exec(t_shell **shell, char *exec, char **ptr, char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	if (!path)
		path = "/usr/bin:/bin:/usr/sbin:/sbin";
	if ((exec = get_full_executable(shell, exec, path)))
	{
		fork_and_execute(shell, exec, ptr, env);
		ft_strdel(&exec);
	}
	else
		command_not_found(shell);
}

void		interpret_line(t_shell **shell)
{
	char	**ptr;
	char	**env;
	char	*exec;

	exec = NULL;
	ptr = (*shell)->cmd;
	env = (*shell)->env;
	if (try_a_builtin(shell))
		return ;
	must_exec(shell, exec, ptr, env);
}
