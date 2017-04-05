/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:00:23 by moska             #+#    #+#             */
/*   Updated: 2017/04/05 07:07:33 by adeletan         ###   ########.fr       */
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

int		env_var_error_checking(char *env_str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!env_str || (!(ft_isalpha(env_str[i]) || env_str[i] == '_')))
	{
		ft_putstr_fd("setenv: bad env var name: ", 2);
		ft_putendl_fd(env_str, 2);
		ret = -1;
	}
	i++;
	while (env_str && env_str[i])
	{
		if (!(ft_isalnum(env_str[i]) || env_str[i] == '_'))
		{
			ft_putstr_fd("setenv: bad env var name: ", 2);
			ft_putendl_fd(env_str, 2);
			ret = -1;
			break ;
		}
		i++;
	}
	g_exit_code = ret;
	return (ret);
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
		if (env_var_error_checking((*shell)->cmd[1]) == -1)
			return (-1);
		do_setenv(shell, (*shell)->cmd[1], (*shell)->cmd[2]);
	}
	return (0);
}
