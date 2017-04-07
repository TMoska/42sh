/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/08 01:14:13 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_pad		start_pad(struct winsize w, size_t nb_files)
{
	struct s_pad	pad;

	pad.line_s = 1;
	pad.col_s = 1;
	pad.page_s = 1;
	pad.pages = 1;
	pad.cols = 1;
	pad.max_x = w.ws_col - 2;
	pad.max_y = 10;
	while (nb_files > pad.cols * pad.pages)
		(pad.cols < 5 ? pad.cols++ : pad.pages++);
	pad.len_x = 0;
	return (pad);
}

static t_c_tab		*cmd_option_2(t_c_tab *tmp, char *cmd)
{
	if (!(tmp = (t_c_tab*)malloc(sizeof(t_c_tab))))
		return (NULL);
	tmp->cursor = 0;
	tmp->place = 0;
	tmp->col = 0;
	tmp->page = 0;
	tmp->name = NULL;
	tmp->perm = NULL;
	if (check_dir(cmd) == 1)
		tmp->content = ft_strjoin(cmd, "/");
	else
		tmp->content = ft_strdup(cmd);
	return (tmp);
}

t_c_tab				*cmd_option(char *cmd, t_c_tab *list)
{
	t_c_tab			*tmp;
	t_c_tab			*prev;

	tmp = NULL;
	if (!list)
	{
		tmp = cmd_option_2(tmp, cmd);
		list = tmp;
		tmp->prev = NULL;
		get_list(tmp, 1);
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		prev = tmp;
		tmp = tmp->next;
		tmp = cmd_option_2(tmp, cmd);
		prev->next = tmp;
		tmp->prev = prev;
	}
	tmp->next = NULL;
	return (list);
}
