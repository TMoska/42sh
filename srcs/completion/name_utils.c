/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 06:28:31 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/09 12:52:53 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*completion_buffer(t_c_tab *list, t_shell *shell)
{
	char *tmp;
	char *start;
	char *end;

	tmp = search_cmd(shell);
	if (!tmp || tmp[0] == '\0')
	{
		start = ft_strsub(shell->buff, 0, shell->term->tc_in);
		end = ft_strsub(shell->buff, shell->term->tc_in,
			shell->term->tc_len - shell->term->tc_in);
		ft_strdel(&shell->buff);
		shell->buff = ft_str3join(start, list->content, end);
		ft_strdel(&start);
		ft_strdel(&end);
	}
	else
		ft_str_replace(&(shell->buff), tmp, list->content, 1);
	ft_strdel(&tmp);
	tmp = ft_strdup(shell->buff);
	ft_bzero(shell->buff, ft_strlen(shell->buff));
	return (tmp);
}

char		*fix_cmdname(char **cmd)
{
	char	*tmp;
	char	*to_find;
	size_t	len;

	len = ft_strlen(*cmd);
	tmp = ft_strrchr(*cmd, '/');
	if (!tmp)
	{
		to_find = ft_strdup(*cmd);
		ft_strdel(cmd);
		*cmd = ft_strdup("");
		return (to_find);
	}
	to_find = ft_strdup(tmp + 2);
	len = len - (ft_strlen(tmp) - 2);
	tmp = ft_strndup(*cmd, len);
	ft_strdel(cmd);
	*cmd = tmp;
	return (to_find);
}

t_c_tab		*get_matching(t_c_tab *list, char *path, char *tofind)
{
	DIR				*dir;
	struct dirent	*dp;

	if (!path || path[0] == '\0')
	{
		if (!(dir = opendir(".")))
			return (NULL);
	}
	else if (!(dir = opendir(path)))
		return (NULL);
	while ((dp = readdir(dir)) != NULL)
		if (dp->d_name[0] != '.')
			if (ft_strncmp(dp->d_name, tofind, ft_strlen(tofind)) == 0)
				list = cmd_option(dp->d_name, list);
	closedir(dir);
	return (list);
}
