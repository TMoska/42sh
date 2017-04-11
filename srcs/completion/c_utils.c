/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/11 17:22:39 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t				binary_directories(t_shell *shell)
{
	char			**split;
	size_t			val;
	size_t			in;

	in = shell->term->tc_in;
	while (in > 0 && shell->buff[in] != '|' && shell->buff[in] != '`' &&
			shell->buff[in] != '&' && shell->buff[in] != ';')
		in--;
	(in != 0 ? in++ : 0);
	if (!(split = ft_strsplit((shell->buff + in), ' ')))
		return (1);
	val = 0;
	if (split[0] == NULL || (split[0] != NULL &&
				(split[1] == NULL || split[1][0] == '\0') &&
				shell->buff[shell->term->tc_in - 1] != ' '))
		val = 1;
	ft_str2del(&split);
	return (val);
}

char				*search_cmd(t_shell *shell)
{
	char			*tmp;
	size_t			i;
	size_t			in;

	in = shell->term->tc_in;
	if (in != 0 && (shell->buff[in] == '/' && shell->buff[in - 1] == '.' &&
				(shell->buff[in + 1] == '\0' || shell->buff[in + 1] == ' ')))
		return (ft_strsub(shell->buff, in - 1, in + 1));
	while (in > 0 && shell->buff[in] != '|' && shell->buff[in] != '`' &&
			shell->buff[in] != '&' && shell->buff[in] != ';')
		in--;
	(in != 0 ? in++ : 0);
	if (shell->term->tc_in == 0 || (shell->buff[in] == ' ' &&
				shell->buff[in + 1] == '\0'))
		return (ft_strdup(""));
	i = shell->term->tc_in;
	in = i;
	while (i != 0 && ((((shell->buff)[i] != ' ') &&
					!ft_isquotes(shell->buff[i])) || i == in))
		i--;
	(i != 0 ? i++ : 0);
	while ((shell->buff)[in] != '\0' && (shell->buff)[in] != ' ')
		in++;
	tmp = ft_strsub(shell->buff, i, in - i);
	return (tmp);
}

t_c_tab				*option_dir(DIR *dir, t_c_tab *list, char **cmd)
{
	struct dirent	*dp;
	t_c_tab			*tmp;
	char			*tmp2;

	while ((dp = readdir(dir)) != NULL)
		if (dp->d_name[0] != '.')
			list = cmd_option(dp->d_name, list);
	closedir(dir);
	tmp = list;
	while (tmp && tmp->content)
	{
		tmp2 = ft_strjoin((*cmd), tmp->content);
		ft_strdel(&tmp->content);
		if (tmp2[ft_strlen(tmp2) - 1] != '/' && check_dir(tmp2) == 1)
			tmp->content = ft_strjoin(tmp2, "/");
		else
			tmp->content = ft_strdup(tmp2);
		ft_strdel(&tmp2);
		tmp = tmp->next;
	}
	tab_lst_sort(&list);
	list = tab_name(list, *cmd);
	ft_strdel(cmd);
	return (list);
}

/*
**				cmd_options is on c_utils2.c
*/

t_c_tab				*search_on_dir(char *path, t_shell *shell, t_c_tab *list,
		size_t bin)
{
	DIR				*dir;
	char			*cmd;
	struct dirent	*dp;
	size_t			len;

	cmd = search_cmd(shell);
	len = ft_strlen(cmd);
	if (bin == 1 && (dir = opendir(cmd)))
		return ((list = option_dir(dir, list, &cmd)));
	else if (bin == 1 && !(dir = opendir(cmd)))
		return ((list = name_completion(list, &cmd)));
	else if (!(dir = opendir(path)))
		return (NULL);
	signal(SIGINT, SIG_IGN);
	while ((dp = readdir(dir)) != NULL)
		if ((dp->d_name[0] != '.' || (cmd && cmd[0] == '.')) &&
				!compare_tab_str(cmd, dp->d_name, len))
			list = cmd_option(dp->d_name, list);
	closedir(dir);
	tab_lst_sort(&list);
	(list && list->content) ? (list = tab_name(list, cmd)) : (0);
	(list && list->content && list->name) ? (list->cursor = 1) : (0);
	ft_strdel(&cmd);
	signal(SIGINT, sig_callback);
	return (list);
}
