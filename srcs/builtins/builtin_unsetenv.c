/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:27:38 by moska             #+#    #+#             */
/*   Updated: 2017/04/05 15:45:45 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hanlde_cmd(t_shell **shell, char **cmd)
{
	t_envl	*tmp;
	t_envl	*prev;

	tmp = (*shell)->env_list;
	prev = NULL;
	if (!tmp)
		return ;
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
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		free(tmp);
	}
}

int		builtin_unsetenv(t_shell **shell)
{
	char	**cmd;

	cmd = (*shell)->cmd;
	if ((*shell)->cmd_len == 1)
		return (-1);
	cmd++;
	while (*cmd)
		hanlde_cmd(shell, cmd++);
	rebuild_str2env(shell);
	return (0);
}
