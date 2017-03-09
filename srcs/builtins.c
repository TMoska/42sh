/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:56:19 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 08:55:54 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_a_builtin(t_shell **shell)
{
	int		ret;

	ret = 1;
	if (ft_strcmp((*shell)->cmd[0], "exit") == 0)
		builtin_exit(shell);
	else if (ft_strcmp((*shell)->cmd[0], "env") == 0)
		builtin_env(shell);
	else if (ft_strcmp((*shell)->cmd[0], "getenv") == 0)
		builtin_getenv(shell);
	else if (ft_strcmp((*shell)->cmd[0], "setenv") == 0)
		builtin_setenv(shell);
	else if (ft_strcmp((*shell)->cmd[0], "unsetenv") == 0)
		builtin_unsetenv(shell);
	else if (ft_strcmp((*shell)->cmd[0], "cd") == 0)
		builtin_cd(shell);
	else if (ft_strcmp((*shell)->cmd[0], "echo") == 0)
		builtin_echo(shell);
	else if (ft_strcmp((*shell)->cmd[0], "hist") == 0)
		print_history(shell);
	else if (ft_strcmp((*shell)->cmd[0], "clean") == 0)
		clean_terminal();
	else
		ret = 0;
	return (ret);
}
