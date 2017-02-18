/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 22:30:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/18 20:28:43 by tmoska           ###   ########.fr       */
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

char	*get_env_val(t_envl *begin_list, char *name)
{
	while (begin_list)
	{
		if (ft_strcmp(begin_list->name, name) == 0)
			return (begin_list->value);
		else
			begin_list = begin_list->next;
	}
	return (NULL);

}

void	clean_env_list(t_envl **begin_list)
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