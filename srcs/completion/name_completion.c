/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 06:26:54 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/09 23:19:23 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_c_tab		*fill_binary(t_c_tab *list, char *path, char *tofind)
{
	char	*tmp;

	tmp = ft_strdup(path);
	if (!(list = get_matching_binary(list, path, tofind)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	tab_lst_sort(&list);
	list = tab_name(list, tmp);
	ft_strdel(&tmp);
	return (list);
}

t_c_tab				*binary_directory(t_c_tab *list, t_shell *shell)
{
	char *tofind;
	char *path;

	(void)list;
	path = search_cmd(shell);
	if (!ft_strchr(path, '/'))
	{
		ft_strdel(&path);
		return (NULL);
	}
	tofind = fix_cmdname(&path);
	if (!(list = fill_binary(list, path, tofind)))
	{
		ft_strdel(&tofind);
		return (NULL);
	}
	ft_strdel(&tofind);
	get_list(list, 1);
	return (list);
}

t_c_tab				*name_fill(t_c_tab *list, char *path, char *tofind)
{
	t_c_tab			*tmp;
	char			*tmp2;

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

t_c_tab				*name_completion(t_c_tab *list, char **path)
{
	char *tofind;

	(void)list;
	tofind = fix_cmdname(path);
	if (!(list = name_fill(list, *path, tofind)))
	{
		ft_strdel(&tofind);
		return (NULL);
	}
	ft_strdel(&tofind);
	return (list);
}
