/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by moska             #+#    #+#             */
/*   Updated: 2017/02/18 20:22:11 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_shell **shell, int terminated)
{
	// Todo: show working directory on the left
	if (terminated)
		write(1, "\n> ", 3);
	else
	{
		ft_putstr("\033[0;32m");
		ft_putstr(get_env_val((*shell)->env_list, "PWD"));
		ft_putstr("> ");
		ft_putstr("\033[0m");
	}
}

void	command_not_found(t_shell **shell)
{
	printf("%s\n", (*shell)->cmd[0]);
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	permission_denied(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
