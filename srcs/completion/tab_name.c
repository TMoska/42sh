/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 03:07:18 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/06 06:34:17 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_c_tab	*tab_name(t_c_tab *list, char *cmd)
{
	t_c_tab *tmp;
	char	*tmpstr;

	tmp = list;
	tmpstr = ft_strrchr(cmd, '/');
	while (tmp)
	{
		tmp->name = ft_strdup(tmp->content);
		if (tmpstr)
		{
			ft_str_replace(&(tmp->name), cmd, "", 1);
		}
		if (tmp->name[ft_strlen(tmp->name) - 1] == '/')
			tmp->name = ft_strndelat(tmp->name, ft_strlen(tmp->name) - 1, 1);
		get_info(tmp);
		if (!cmd)
			return (list);
		tmp = tmp->next;
	}
	return (list);
}
