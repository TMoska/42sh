/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/04/11 03:23:02 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(t_shell **shell, char *exec, char **ptr, char **env)
{
	int		status;
	pid_t	pid;

	if (((pid = fork()) == -1) && fork_error())
		(*shell)->ret = -1;
	else if (!pid)
	{
		if (execve(exec, ptr, env) == -1)
		{
			ft_putendl_fd("42sh: exec format error.", 2);
			(*shell)->ret = -1;
			exit((*shell)->ret);
		}
		(*shell)->ret = 0;
		exit((*shell)->ret);
	}
	else
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		(*shell)->ret = WEXITSTATUS(status);
	}
	return ((*shell)->ret);
}

int			test_n_execute(char *exec, char **ptr, char **env)
{
	t_shell	*shell;
	int		ret;

	shell = get_shell(NULL);
	ret = 0;
	if (ft_strcmp(ptr[0], "env") != 0 && fix_path_if_going_home(&shell) == -1)
	{
		ft_str2del(&(shell->cmd));
		return (-1);
	}
	if ((ret = try_a_builtin(&shell, ptr[0])) < 1)
	{
		ft_str2del(&(shell->cmd));
		return (ret);
	}
	ret = -1;
	if (get_and_test_executable(&shell, &exec, env) == 0)
	{
		term_trigger(&shell, 1);
		ret = execute(&shell, exec, ptr, env);
		term_trigger(&shell, 0);
	}
	ft_strdel(&exec);
	ft_str2del(&(shell->cmd));
	return (ret);
}

int			interpret_line(char *cmd)
{
	char	**ptr;
	char	**env;
	char	*exec;
	t_shell	*shell;
	int		ret;

	shell = get_shell(NULL);
	shell->cmd = ft_splittreat(cmd, ' ');
	shell->cmd_len = ft_str2len(shell->cmd);
	exec = NULL;
	ptr = shell->cmd;
	rebuild_str2env(&shell);
	env = shell->env;
	ret = test_n_execute(exec, ptr, env);
	return (ret);
}
