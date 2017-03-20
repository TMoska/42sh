/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/20 04:17:49 by tmoska           ###   ########.fr       */
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
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_strsplit(path, ':');
	if ((tmp = loop_through_paths(&paths, &i, cmd)))
		return (tmp);
	ft_str2del(&paths);
	return (NULL);
}

static int	execute(t_shell **shell, char *exec, char **ptr, char **env)
{
	int		ret;
	int		status;

	ret = 0;
	if (fork() == 0)
	{
		execve(exec, ptr, env);
		ret = -1;
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			(*shell)->ret = WIFEXITED(status);
			g_exit_code = WIFEXITED(status);
			if (WEXITSTATUS(status))
				ret = -1;
		}
	}
	return (ret);
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

int			get_and_test_executable(t_shell **shell, char **exec)
{
	char	*path;
	int		i;

	i = 0;
	path = get_env_val(shell, "PATH");
	if ((*exec = get_full_executable(shell, *exec, path)))
		return (fork_and_execute(shell, *exec));
	else
		return (command_not_found(shell));
}

int			test_n_execute(t_shell **shell, char *exec, char **ptr, char **env)
{
	int		ret;

	ret = 0;
	if (get_and_test_executable(shell, &exec) == 0)
	{
		term_trigger(shell, 1);
		ret = execute(shell, exec, ptr, env);
		ft_strdel(&exec);
		term_trigger(shell, 0);
		return (ret);
	}
	return (-1);
}

int			interpret_line(char *cmd)
{
	char	**ptr;
	char	**env;
	char	*exec;
	t_shell	*shell;
	int		ret;

	shell = get_shell(NULL);
	shell->cmd = ft_strsplit(cmd, ' ');
	shell->cmd_len = ft_str2len(shell->cmd);
	exec = NULL;
	ptr = shell->cmd;
	rebuild_str2env(&shell);
	env = shell->env;
	ret = try_a_builtin(&shell, ptr[0], cmd);
	if (ret < 1)
		return (ret);
	ret = test_n_execute(&shell, exec, ptr, env);
	ft_str2del(&(shell->cmd));
	return (ret);
}
