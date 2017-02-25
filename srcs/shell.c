/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:29:07 by moska             #+#    #+#             */
/*   Updated: 2017/02/25 20:21:20 by moska            ###   ########.fr       */
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

static void	increment_shlvl(t_shell **shell)
{
	char *shlvl;

	shlvl = get_env_val(shell, "SHLVL");
	printf("SHELL1: %s\n", shlvl);
	if (!shlvl)
		shlvl = "1";
	else
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	printf("SHELL2: %s\n", shlvl);
	do_setenv(shell, "SHLVL", shlvl);
}

static void	set_env(t_shell **shell, char **env)
{
	(*shell)->env = ft_str2dup(env);
	(*shell)->env_list = built_env_list((*shell)->env);
	increment_shlvl(shell);
}

void		create_shell(t_shell **shell, char **env)
{
	if ((*shell = ft_memalloc(sizeof(t_shell))))
	{
		(*shell)->exit = 0;
		(*shell)->ret = 0;
		g_exit_code = 0;
		(*shell)->cmd_len = 0;
		ft_bzero(&(*shell)->commands, sizeof(t_list*));
	}
	set_env(shell, env);
}
