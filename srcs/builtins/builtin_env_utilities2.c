/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utilities2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:28:01 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 20:56:47 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_null(char *a)
{
	return (ft_strcmp("-0", a) == 0 || ft_strcmp("--null", a) == 0);
}

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

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			size++;
		i++;
	}
	return (size);
}

char	**build_tmp_environment(char **cmd)
{
	char	**env;
	int		i;
	int		a;
	size_t	size;

	a = 0;
	i = 0;
	size = setenvs_count(cmd);
	env = ft_str2new(size);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			env[a] = ft_strdup(cmd[i]);
			a++;
		}
		i++;
	}
	return (env);
}
