/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:29:07 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 21:06:05 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envl		*built_env_list(char **env)
{
	t_envl	*new;
	char	**tmp_env;

	tmp_env = NULL;
	new = NULL;
	while (*env)
	{
		tmp_env = ft_strsplit(*env, '=');
		if (ft_strcmp(tmp_env[0], "OLDPWD") != 0)
			envladd_back(&new, envlnew(tmp_env[0], tmp_env[1]));
		ft_str2del(&tmp_env);
		env++;
	}
	return (new);
}

static void	set_env(t_shell **shell, char **env)
{
	(*shell)->env = ft_str2dup(env);
	if (ft_str2len(env) == 0)
	{
		// Todo: handle empty environment
	}
	else
		(*shell)->env_list = built_env_list((*shell)->env);
}

void		create_shell(t_shell **shell, char **env)
{
	if ((*shell = ft_memalloc(sizeof(t_shell))))
	{
		(*shell)->exit = 0;
		(*shell)->ret = 0;
		g_exit_code = 0;
		(*shell)->cmd_len = 0;
	}
	set_env(shell, env);
}
