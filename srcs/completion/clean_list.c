/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 01:26:58 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/07 01:44:45 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_list(t_c_tab *list)
{
	t_c_tab *tmp;

	tmp = list;
	while (list)
	{
		ft_strdel(&list->content);
		ft_strdel(&list->name);
		ft_strdel(&list->perm);
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
