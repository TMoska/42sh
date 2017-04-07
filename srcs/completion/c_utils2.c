/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/07 09:22:41 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void				put_question(size_t i)
{
	DEL_LINES;
	MOVE_UP;
	ft_putstr(tgetstr("sc", NULL));
	ft_putstr("\033[1;91m Bro, there is a lot of possibilities O.O like ");
	ft_putnbr(i);
	ft_putstr(" possibilities O.O Are you sure about that? (y or n)\033[0m");
	ft_putstr(tgetstr("rc", NULL));
}
