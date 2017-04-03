/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_prints.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:16:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/04 01:42:00 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_setenv(char **cmd)
{
	char	**env;
	int		i;

	env = build_tmp_environment(cmd);
	env = remove_duplicate_envs(env);
	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
	ft_str2del(&env);
}

char		**get_command(char **command)
{
	int i;
	int u;

	i = 1;
	u = 0;
	while (command[i])
	{
		if (u == 0 && is_ignore(command[i]))
			i++;
		else if (u == 0 && ft_strcmp(command[i], "-u") == 0 && command[i + 1])
			i = i + 2;
		else if (is_setenv(command[i]))
		{
			u = 1;
			i++;
		}
		else
			break ;
	}
	return (&command[i]);
}

void		work_as_newenv(char **cmd, t_shell **shell)
{
	char	**tmp;

	tmp = build_tmp_environment(cmd);
	tmp = remove_duplicate_envs(tmp);
	execute_further(shell, cmd, tmp);
	ft_str2del(&tmp);
}

void		work_with_alterenv(char **cmd, t_shell **shell)
{
	char	**tmp;
	char	**joint;

	tmp = build_tmp_environment(cmd);
	tmp = remove_duplicate_envs(tmp);
	joint = join_envs((*shell)->env, tmp);
	ft_str2del(&tmp);
	execute_further(shell, cmd, joint);
	ft_str2del(&joint);
}

void		work_environ_and_display(char **cmd, t_shell **shell,\
	t_env_s *env_s)
{
	char	**tmp;
	char	**joint;
	t_envl	*env_list;

	tmp = build_tmp_environment(cmd);
	joint = tmp;
	tmp = remove_duplicate_envs(tmp);
	(env_s->ignore != 1) ? joint = join_envs((*shell)->env, tmp) : (0);
	env_list = built_env_list(joint);
	ft_str2del(&tmp);
	print_env(env_list);
	clean_env_list(&env_list);
	(env_s->ignore != 1) ? ft_str2del(&joint) : (0);
}
