/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/04/02 09:49:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(t_shell **shell, char *exec, char **ptr, char **env)
{
	int		ret;
	int		status;
	pid_t	pid;

	ret = 0;
	if (((pid = fork()) == -1) && fork_error())
		ret = -1;
	else if (!pid)
	{
		execve(exec, ptr, env);
		ret = -1;
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		(*shell)->ret = WEXITSTATUS(status);
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
			if (WEXITSTATUS(status))
				ret = -1;
		}
	}
	return (ret);
}

int			test_n_execute(char *cmd, char *exec, char **ptr, char **env)
{
	t_shell	*shell;
	int		ret;

	shell = get_shell(NULL);
	ret = 0;
	if (fix_path_if_going_home(&shell) == -1)
		return (-1);
	if ((ret = try_a_builtin(&shell, ptr[0], cmd)) < 1)
	{
		ft_str2del(&(shell->cmd));
		return (ret);
	}
	if (get_and_test_executable(&shell, &exec, env) == 0)
	{
		term_trigger(&shell, 1);
		ret = execute(&shell, exec, ptr, env);
		ft_strdel(&exec);
		term_trigger(&shell, 0);
		ft_str2del(&(shell->cmd));
		return (ret);
	}
	ft_strdel(&exec);
	ft_str2del(&(shell->cmd));
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
	shell->cmd = ft_splitquotes(cmd, ' ');
	shell->cmd_len = ft_str2len(shell->cmd);
	exec = NULL;
	ptr = shell->cmd;
	rebuild_str2env(&shell);
	env = shell->env;
	ret = test_n_execute(cmd, exec, ptr, env);
	return (ret);
}
