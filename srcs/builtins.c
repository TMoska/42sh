/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:56:19 by moska             #+#    #+#             */
/*   Updated: 2017/03/11 17:50:08 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_a_builtin(t_shell **shell, char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit(shell));
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd, "getenv") == 0)
		return (builtin_getenv(shell));
	else if (ft_strcmp(cmd, "setenv") == 0)
		return (builtin_setenv(shell));
	else if (ft_strcmp(cmd, "unsetenv") == 0)
		return (builtin_unsetenv(shell));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(shell));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(shell));
	// else if (ft_strcmp(cmd, "hist") == 0)
	// 	return (print_history(shell));
	else if (ft_strcmp(cmd, "clean") == 0)
		return (clean_terminal());
	else
		return (1);
}
