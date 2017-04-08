/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 06:26:54 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/08 07:31:25 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_c_tab		*name_fill(t_c_tab *list, char *path, char *tofind)
{
	t_c_tab         *tmp;
	char            *tmp2;

	list = get_matching(list, path, tofind);
	tmp = list;
	while (tmp && tmp->content)
	{
		tmp2 = ft_strjoin(path, tmp->content);
		ft_strdel(&tmp->content);
		if (tmp2[ft_strlen(tmp2) - 1] != '/' && check_dir(tmp2) == 1)
			tmp->content = ft_strjoin(tmp2, "/");
		else
			tmp->content = ft_strdup(tmp2);
		ft_strdel(&tmp2);
		tmp = tmp->next;
	}
	tab_lst_sort(&list);
	list = tab_name(list, path);
	ft_strdel(&path);
	return (list);
}

t_c_tab		*name_completion(t_c_tab *list, char **path)
{
	char *tofind;

	(void)list;
	tofind = fix_cmdname(path);
	if(!(list = name_fill(list, *path, tofind)))
	{
		ft_strdel(&tofind);
		return (NULL);
	}
	ft_strdel(&tofind);
	return (list);
}
