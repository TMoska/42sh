/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:52:25 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/04 04:38:51 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loop_through_paths(char ***paths, int *i, char *cmd)
{
	char	*tmp;
	int		paths_count;

	paths_count = (int)ft_str2len(*paths);
	while (*i < paths_count)
	{
		tmp = ft_str3join((*paths)[*i], "/", cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		ft_strdel(&tmp);
		(*i)++;
	}
	return (0);
}

char	*get_env_val_2str(char **env, char *name)
{
	char	*env_name;
	int		i;
	int		y;

	i = 0;
	if (!env || !(*env) || !*(*env))
		return (NULL);
	while (env[i])
	{
		y = 0;
		while (env[i][y] && env[i][y] != '=')
			y++;
		env_name = ft_strndup(env[i], (size_t)y);
		if (ft_strcmp(env_name, name) == 0)
		{
			ft_strdel(&env_name);
			return (&env[i][y + 1]);
		}
		ft_strdel(&env_name);
		i++;
	}
	return (NULL);
}
