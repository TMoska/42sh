/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/30 18:28:58 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				put_2_page(t_c_tab *list, struct s_put *p)
{
	(*p).c_line++;
	(*p).len = ft_strlen(list->content);
	((*p).len > (*p).m_len ? (*p).m_len = (*p).len : (*p).m_len);
	if (list->cursor == 0)
		ft_putstr(list->content);
	else
	{
		ft_putstr("\033[7;92m");
		ft_putstr(list->content);
		ft_putstr("\033[0m");
	}
}

static void				put_page(t_c_tab *tmp, size_t c_page)
{
	struct s_put		p;
	size_t				move_up;

	p.max_len = 0;
	p.c_col = 1;
	while (tmp && tmp->page == c_page)
	{
		move_up = 0;
		p.c_line = 1;
		p.m_len = 0;
		while (tmp && tmp->col == p.c_col && tmp->page == c_page)
		{
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, p.max_len + 1));
			put_2_page(tmp, &p);
			tmp = tmp->next;
			MOVE_DOWN
			move_up++;
		}
		while (move_up-- != 0)
			MOVE_UP
		p.max_len += p.m_len + 2;
		p.c_col++;
	}
}

int						put_options(t_c_tab *tmp)
{
	size_t				c_page;
	t_c_tab				*list;

	list = tmp;
	MOVE_DOWN;
	while (list && list->cursor != 1)
		list = list->next;
	if (!list)
		return (0);
	c_page = list->page;
	while (list->prev && list->page == c_page)
		list = list->prev;
	(list->prev ? list = list->next : list);
	put_page(list, c_page);
	MOVE_UP;
	return (1);
}
