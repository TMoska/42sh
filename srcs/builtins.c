/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:56:19 by moska             #+#    #+#             */
/*   Updated: 2017/03/06 16:15:04 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_a_builtin(t_shell **shell)
{
	int		ret;
	char	*cmd;

	ret = 1;
	cmd = (*shell)->cmd[0];
	if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(shell);
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_env(shell);
	else if (ft_strcmp(cmd, "getenv") == 0)
		builtin_getenv(shell);
	else if (ft_strcmp(cmd, "setenv") == 0)
		builtin_setenv(shell);
	else if (ft_strcmp(cmd, "unsetenv") == 0)
		builtin_unsetenv(shell);
	else if (ft_strcmp(cmd, "cd") == 0)
		builtin_cd(shell);
	else if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(shell);
	else if (ft_strcmp(cmd, "hist") == 0)
		print_history(shell);
	else if (ft_strcmp(cmd, "clean") == 0)
		clean_terminal();
	else if (ft_strcmp(cmd, "export") == 0)
		builtin_export(shell);
	else
		ret = 0;
	return (ret);
}
