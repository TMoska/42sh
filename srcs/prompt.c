/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 22:56:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_shell **shell)
{
	ft_putstr("\033[0;32m");
	ft_putstr(get_env_val(shell, "PWD"));
	ft_putstr("> ");
	ft_putstr("\033[0m");
}

void	command_not_found(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
}

void	permission_denied(t_shell **shell, char *path)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	if (path)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	ft_putendl_fd(": Permission denied", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
}

void	no_file_or_dir(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": no such file or directory: ", 2);
	ft_putendl_fd((*shell)->cmd[1], 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
}
