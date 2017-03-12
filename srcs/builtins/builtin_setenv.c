/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:00:23 by moska             #+#    #+#             */
/*   Updated: 2017/03/12 18:04:13 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_setenv(t_shell **shell, char *name, char *value)
{
	t_envl	*tmp;

	tmp = (*shell)->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	envladd_back(&(*shell)->env_list, envlnew(name, value));
	rebuild_str2env(shell);
}

int		builtin_setenv(t_shell **shell)
{
	size_t	len;

	len = ft_str2len((*shell)->cmd);
	if (len == 1)
		builtin_env(shell);
	else if (len > 3)
	{
		ft_putendl_fd("setenv: too many arguments", 2);
		(*shell)->ret = 2;
		g_exit_code = 2;
		return (-1);
	}
	else
	{
		if (!(ft_isalpha((*shell)->cmd[1][0]) || (*shell)->cmd[1][0] == '_'))
		{
			ft_putstr_fd("setenv: not an identifier: ", 2);
			ft_putendl_fd((*shell)->cmd[1], 2);
			(*shell)->ret = -1;
			g_exit_code = -1;
			return (-1);
		}
		do_setenv(shell, (*shell)->cmd[1], (*shell)->cmd[2]);
	}
	return (0);
}
