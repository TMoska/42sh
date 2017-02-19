/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by moska             #+#    #+#             */
/*   Updated: 2017/02/19 22:38:31 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_shell **shell)
{
	ft_putstr("\033[0;32m");
	ft_putstr(get_env_val((*shell)->env_list, "PWD"));
	ft_putstr("> ");
	ft_putstr("\033[0m");
}

void	command_not_found(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	permission_denied(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
