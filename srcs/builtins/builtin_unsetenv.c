/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:27:38 by moska             #+#    #+#             */
/*   Updated: 2017/03/05 22:09:20 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hanlde_cmd(t_shell **shell, char **cmd)
{
	t_envl	*tmp;
	t_envl	*prev;

	tmp = (*shell)->env_list;
	prev = NULL;
	while (!(ft_strcmp(tmp->name, *cmd) == 0) && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->name, *cmd) == 0)
	{
		if (prev)
			prev->next = tmp->next;
		else
			(*shell)->env_list = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	builtin_unsetenv(t_shell **shell)
{
	char	**cmd;

	cmd = (*shell)->cmd;
	if (ft_str2len(cmd) == 1)
		return ;
	cmd++;
	while (*cmd)
		hanlde_cmd(shell, cmd++);
	rebuild_str2env(shell);
}
