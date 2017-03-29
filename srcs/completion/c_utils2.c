/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/29 09:24:45 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_c_tab		*cmd_option_2(t_c_tab *tmp, char *cmd)
{
	if (tmp->prev)
		tmp->cursor = 0;
	else
		tmp->cursor = 1;
	tmp->place = 0;
	tmp->col = 0;
	tmp->page = 0;
	tmp->content = ft_strdup(cmd);
	return (tmp);
}

t_c_tab				*cmd_option(char *cmd, t_c_tab *list)
{
	t_c_tab			*tmp;
	t_c_tab			*prev;

	if (!list)
	{
		if (!(tmp = (t_c_tab*)malloc(sizeof(t_c_tab))))
			return (NULL);
		list = tmp;
		tmp->prev = NULL;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		prev = tmp;
		tmp = tmp->next;
		if (!(tmp = (t_c_tab*)malloc(sizeof(t_c_tab))))
			return (NULL);
		prev->next = tmp;
		tmp->prev = prev;
	}
	tmp = cmd_option_2(tmp, cmd);
	tmp->next = NULL;
	return (list);
}

static void			clean_c_tab_node(t_c_tab **node)
{
	ft_strdel(&(*node)->content);
	free(*node);
}

void				clean_c_list(t_c_tab **lst)
{
	t_c_tab			*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		clean_c_tab_node(&tmp);
	}
}

void				put_question(size_t i)
{
	DEL_LINES
    ft_putstr("\033[1;91m Bro, there is a lot of possibilities O.O like ");
	ft_putnbr(i);
	ft_putstr(" possibilities O.O Are you sure about that? (y or n)\033[0m");
}
