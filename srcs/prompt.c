/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:33:26 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 16:09:40 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(int terminated)
{
	// Todo: show working directory on the left
	if (terminated)
		write(1, "\n> ", 3);
	else
	{
		ft_putstr("\033[0;32m");
		write(1, "moska prompt $> ", 16);
		ft_putstr("\033[0m");
	}
}

void	command_not_found(t_shell **shell)
{
	ft_putstr_fd((*shell)->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}
