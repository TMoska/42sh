/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_prints.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:16:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/16 16:20:00 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_setenv(char **cmd)
{
	while (*cmd)
	{
		if (ft_strchr(*cmd, '='))
			ft_putendl(*cmd);
		cmd++;
	}
}

char		**get_command(char **command)
{
	int i;
	int u;

	i = 1;
	u = 0;
	while (command[i])
	{
		if (u == 0 && (is_ignore(command[i]) || is_null(command[i])))
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
	char	**ptr;

	tmp = build_tmp_environment(cmd);
	ptr = get_command(cmd);
	test_n_execute(shell, ptr[0], ptr, tmp);
	(void)shell;
	ft_str2del(&tmp);
}

void		work_with_alterenv(char **cmd, t_shell **shell)
{
	char	**tmp;
	char	**ptr;
	char	**joint;

	tmp = build_tmp_environment(cmd);
	joint = ft_str2join((*shell)->env, tmp);
	ft_str2del(&tmp);
	ptr = get_command(cmd);
	test_n_execute(shell, ptr[0], ptr, joint);
	ft_str2del(&joint);
}

void		work_environ_and_display(char **cmd, t_shell **shell)
{
	char	**tmp;
	char	**joint;
	t_envl	*env_list;

	tmp = build_tmp_environment(cmd);
	joint = ft_str2join((*shell)->env, tmp);
	env_list = built_env_list(joint);
	ft_str2del(&tmp);
	print_env(env_list);
	clean_env_list(&env_list);
	ft_str2del(&joint);
}
