/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:29:07 by moska             #+#    #+#             */
/*   Updated: 2017/02/18 20:26:42 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(t_shell **shell, char **env)
{
	char	**tmp_env;

	tmp_env = NULL;
	(*shell)->env = ft_str2dup(env);
	if (ft_str2len(env) == 0)
	{
		// Todo: handle empty environment
	}
	else
	{
		while (*env)
		{
			tmp_env = ft_strsplit(*env, '=');
			envladd_back(&(*shell)->env_list, envlnew(tmp_env[0], tmp_env[1]));
			env++;
		}
	}
}

void		create_shell(t_shell **shell, char **env)
{
	if ((*shell = ft_memalloc(sizeof(t_shell))))
	{
		(*shell)->exit = 0;
		(*shell)->ret = 0;
		(*shell)->cmd_len = 0;
	}
	set_env(shell, env);
}
