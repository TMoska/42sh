/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 22:30:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/17 22:30:52 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envl	*envlnew(char *name, char *value)
{
	t_envl *lst;
	size_t size;

	lst = (t_envl *)ft_memalloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	if (name)
	{
		size = ft_strlen(name);
		if ((lst->name = ft_strnew(size + 1)))
			ft_strcpy(lst->name, name);
		else
			return (NULL);
	}
	if (value)
	{
		size = ft_strlen(value);
		if ((lst->value = ft_strnew(size + 1)))
			ft_strcpy(lst->value, value);
		else
			return (NULL);
	}
	lst->next = NULL;
	return (lst);
}

void	envladd(t_envl **begin_list, t_envl *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

int		envladd_back(t_envl **begin_list, t_envl *new)
{
	t_envl *tmp;

	tmp = *begin_list;
	if (!new)
		return (0);
	if (*begin_list)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		envladd(begin_list, new);
	return (1);
}