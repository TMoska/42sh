/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utilities2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:28:01 by moska             #+#    #+#             */
/*   Updated: 2017/04/05 14:15:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_ignore(char *a)
{
	return (ft_strcmp(a, "-i") == 0 || \
			ft_strcmp(a, "--ignore-environment") == 0);
}

int		is_setenv(char *a)
{
	return (ft_strchr(a, '=') != 0);
}

size_t	setenvs_count(char **cmd)
{
	size_t	size;
	int		i;
	int		found;

	i = 0;
	size = 0;
	found = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			size++;
			found = 1;
		}
		else if (!ft_strchr(cmd[i], '=') && found == 1)
			break ;
		i++;
	}
	return (size);
}

void	check_and_add(char ***cmd, char ***env, int *a, int i)
{
	char	*tmp;

	tmp = ft_strndup((*cmd)[i], ft_strlen_until((*cmd)[i], '='));
	if (env_var_error_checking(tmp) != -1)
	{
		(*env)[*a] = ft_strdup((*cmd)[i]);
		(*a)++;
	}
	ft_strdel(&tmp);
}

char	**build_tmp_environment(char **cmd)
{
	char	**env;
	int		i;
	int		found;
	int		a;
	size_t	size;

	a = 0;
	i = 0;
	found = 0;
	size = setenvs_count(cmd);
	env = ft_str2new(size);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			found = 1;
			check_and_add(&cmd, &env, &a, i);
		}
		else if (!ft_strchr(cmd[i], '=') && found)
			break ;
		i++;
	}
	return (env);
}
