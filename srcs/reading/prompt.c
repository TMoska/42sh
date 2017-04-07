/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/07 09:06:48 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_shell **shell, char *prompt)
{
	ft_putstr("\033[0;33m[\033[0;32m");
	if (!prompt)
	{
		build_prompt(shell);
		ft_putendl("\033[0;33m]\033[0m ");
		ft_putstr("$ ");
		(*shell)->term->prompt_len = 2;
	}
	else
	{
		ft_putstr(prompt);
		ft_putstr("\033[0;33m]\033[0m ");
		(*shell)->term->prompt_len = ft_strlen(prompt) + 3;
	}
	ft_strdel(&prompt);
}

int		command_not_found(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
	return (-1);
}

int		permission_denied(t_shell **shell, t_bool name, char *path)
{
	if (name)
		ft_putstr_fd((*shell)->cmd[0], 2);
	if (path)
	{
		if (name)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	ft_putendl_fd(": Permission denied", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
	return (-1);
}

void	no_file_or_dir(t_shell **shell, t_bool name)
{
	if (name)
	{
		ft_putstr_fd((*shell)->cmd[0], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd("no such file or directory", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
}

void	not_a_dir(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putendl_fd(": not a directory", 2);
	(*shell)->ret = -1;
	g_exit_code = -1;
}
