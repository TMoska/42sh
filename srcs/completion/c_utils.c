/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/31 04:00:15 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char			**split;
	char			*tmp;
	size_t			i;
	size_t			in;

	in = shell->term->tc_in;
	while (in > 0 && shell->buff[in] != '|' && shell->buff[in] != '`' &&
			shell->buff[in] != '&' && shell->buff[in] != ';')
		in--;
	(in != 0 ? in++ : 0);
	if (!(split = ft_strsplit((shell->buff + in), ' ')))
		return (NULL);
	if (shell->buff[shell->term->tc_in - 1] == ' ')
	{
		ft_str2del(&split);
		return (ft_strdup(""));
	}
	i = 0;
	while (split[i + 1] != NULL)
		i++;
	tmp = ft_strdup(split[i]);
	ft_str2del(&split);
	return (tmp);
}

t_c_tab				*search_on_dir(char *path, t_shell *shell, t_c_tab *list)
{
	DIR				*dir;
	char			*cmd;
	struct dirent	*dp;
	size_t			len;

	cmd = search_cmd(shell);
	len = ft_strlen(cmd);
	if (!(dir = opendir(path)))
		return (NULL);
	while ((dp = readdir(dir)) != NULL)
		if ((dp->d_name[0] != '.' || (cmd && cmd[0] == '.')) &&
				!ft_strncmp(cmd, dp->d_name, len))
			list = cmd_option(dp->d_name, list);
	ft_strdel(&cmd);
	return (list);
}
