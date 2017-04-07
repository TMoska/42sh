/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 03:07:18 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/07 09:10:41 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_c_tab	*tab_name(t_c_tab *list, char *cmd)
{
	t_c_tab *tmp;
	char	*tmp_str;

	tmp = list;
	while (tmp)
	{
		tmp_str = tmp->name;
		tmp->name = ft_strdup(tmp->content);
		ft_strdel(&tmp_str);
		if (ft_strrchr(cmd, '/'))
			ft_str_replace(&(tmp->name), cmd, "", 1);
		if (tmp->name[ft_strlen(tmp->name) - 1] == '/')
		{
			tmp_str = tmp->name;
			tmp->name = ft_strndelat(tmp->name, ft_strlen(tmp->name) - 1, 1);
			ft_strdel(&tmp_str);
		}
		if (!tmp->perm)
			get_info(tmp);
		if (!cmd)
			return (list);
		tmp = tmp->next;
	}
	return (list);
}
