/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:56:19 by moska             #+#    #+#             */
/*   Updated: 2017/04/06 00:48:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_a_builtin(t_shell **shell, char *base_cmd)
{
	if (ft_strcmp(base_cmd, "exit") == 0)
		return (builtin_exit(shell));
	else if (ft_strcmp(base_cmd, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(base_cmd, "getenv") == 0)
		return (builtin_getenv(shell));
	else if (ft_strcmp(base_cmd, "setenv") == 0)
		return (builtin_setenv(shell));
	else if (ft_strcmp(base_cmd, "unsetenv") == 0)
		return (builtin_unsetenv(shell));
	else if (ft_strcmp(base_cmd, "cd") == 0)
		return (builtin_cd(shell));
	else if (ft_strcmp(base_cmd, "echo") == 0)
		return (builtin_echo(shell));
	else if (ft_strcmp(base_cmd, "history") == 0)
		return (print_history(shell));
	else if (ft_strcmp(base_cmd, "clean") == 0)
		return (clean_terminal());
	else
		return (1);
}
