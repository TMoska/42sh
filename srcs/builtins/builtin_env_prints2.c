/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_prints2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:57:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/08 22:02:25 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		compare_and_del(char ***shell_env, char **new, int x, int *y)
{
	char	*tmp_env;
	char	*tmp_new;

	tmp_env = ft_strndup((*shell_env)[*y],\
				ft_strlen_until((*shell_env)[*y], '='));
	tmp_new = ft_strndup(new[x], ft_strlen_until(new[x], '='));
	if (ft_strcmp(tmp_env, tmp_new) == 0)
		*shell_env = ft_arr_del_at(*shell_env, *y);
	else
		(*y)++;
	ft_strdel(&tmp_env);
	ft_strdel(&tmp_new);
}

char		**join_envs(char **env, char **new)
{
	char	**joint;
	char	**shell_env;
	int		x;
	int		y;

	x = 0;
	if (!(shell_env = ft_str2dup(env)))
		return (NULL);
	while (new[x])
	{
		y = 0;
		while (shell_env[y])
			compare_and_del(&shell_env, new, x, &y);
		x++;
	}
	joint = ft_str2join(shell_env, new);
	ft_str2del(&shell_env);
	return (joint);
}

char		**remove_duplicate_envs(char **env)
{
	char	*tmp_x;
	char	*tmp_y;
	int		x;
	int		y;

	x = -1;
	while (env[++x])
	{
		tmp_x = ft_strndup(env[x], ft_strlen_until(env[x], '='));
		y = 0;
		while (env[x + ++y])
		{
			tmp_y = ft_strndup(env[x + y], ft_strlen_until(env[x + y], '='));
			if (ft_strcmp(tmp_x, tmp_y) == 0)
			{
				env = ft_arr_del_at(env, x--);
				ft_strdel(&tmp_y);
				break ;
			}
			ft_strdel(&tmp_y);
		}
		ft_strdel(&tmp_x);
	}
	return (env);
}

void		execute_further(t_shell **shell, char **cmd, char ***env)
{
	char		**tmp_env;
	char		**ptr;
	char		*commands;
	char		**cmd_tmp;
	t_envl		*envl_list;

	ptr = get_command(cmd);
	cmd_tmp = (*shell)->cmd;
	commands = ft_arr_to_str(ptr);
	tmp_env = (*shell)->env;
	(*shell)->env = *env;
	(*shell)->cmd = ft_splittreat(commands, ' ');
	(*shell)->cmd_len = ft_str2len((*shell)->cmd);
	envl_list = (*shell)->env_list;
	(*shell)->env_list = built_env_list(*env);
	test_n_execute(ptr[0], ptr, *env);
	ft_strdel(&commands);
	(*shell)->cmd = cmd_tmp;
	(*shell)->cmd_len = ft_str2len(cmd_tmp);
	ft_str2del(&(*shell)->env);
	(*shell)->env = tmp_env;
	clean_env_list(&(*shell)->env_list);
	(*shell)->env_list = envl_list;
}
