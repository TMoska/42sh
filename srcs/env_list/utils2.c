/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:53:21 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 21:03:03 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		rebuild_str2env(t_shell **shell)
{
	t_envl	*tmp;
	char	**new;
	int		i;

	i = 0;
	tmp = (*shell)->env_list;
	new = ft_str2new(env_lst_size(tmp));
	while (tmp)
	{
		new[i] = ft_str3join(tmp->name, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	ft_str2del(&(*shell)->env);
	(*shell)->env = new;
}

void		clean_env_list(t_envl **begin_list)
{
	t_envl *tmp;

	while (*begin_list)
	{
		tmp = *begin_list;
		ft_strdel(&((*begin_list)->name));
		ft_strdel(&((*begin_list)->value));
		free(*begin_list);
		*begin_list = tmp->next;
	}
}
