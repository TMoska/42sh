/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:57:06 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 16:08:07 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("%s\n", cmd[i]);
		i++;
	}
}

void	interpret_line(t_shell **shell)
{
	// print_tab((*shell)->cmd);
	// interpretor ??
	if (try_a_builtin(shell))
		return ;
	// else if()
	//   // Fork and look for executable
	else
		command_not_found(shell);
}
