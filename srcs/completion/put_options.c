/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/09 22:56:04 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				put_2_page(t_c_tab *list, struct s_put *p)
{
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, (*p).max_len + 1));
	(*p).c_line++;
	(*p).len = ft_strlen(list->name) + 1;
	((*p).len > (*p).m_len ? (*p).m_len = (*p).len : (*p).m_len);
	if (list->cursor == 0)
		ft_print(list);
	else
	{
		ft_putstr("\033[7;92m");
		ft_putstr(list->name);
		get_extention(list);
		ft_putstr("\033[0m");
	}
}

static int				print_page(size_t c_page, size_t a_page)
{
	MOVE_DOWN;
	ft_putstr(" \033[95mPAGE : ");
	ft_putnbr(c_page);
	ft_putstr(" / ");
	ft_putnbr(a_page);
	ft_putstr("\033[0m");
	MOVE_UP;
	return (1);
}

static void				put_page(t_c_tab *tmp, size_t c_page, size_t a_page)
{
	struct s_put		p;
	size_t				move_up;

	p.max_len = 0;
	p.c_col = 1;
	MOVE_UP;
	while (tmp && tmp->page == c_page)
	{
		move_up = 0;
		p.c_line = 1;
		p.m_len = 0;
		while (tmp && tmp->col == p.c_col && tmp->page == c_page)
		{
			put_2_page(tmp, &p);
			tmp = tmp->next;
			MOVE_DOWN;
			move_up++;
		}
		((p.c_col == 1) ? (print_page(c_page, a_page)) : (0));
		while (move_up-- != 0)
			MOVE_UP;
		p.max_len += p.m_len + 2;
		p.c_col++;
	}
	MOVE_DOWN;
}

int						put_options_2(t_c_tab *list, size_t a_page, size_t val)
{
	size_t				c_page;
	char				*buff[5];

	c_page = list->page;
	while (list->prev && list->page == c_page)
		list = list->prev;
	(list->prev ? list = list->next : list);
	put_page(list, c_page, a_page);
	MOVE_UP;
	if (val == 0 && read(0, buff, 5) && (unsigned int)*buff != BTN_TAB)
		return (0);
	else if (val == 0)
	{
		list->cursor = 1;
		put_options(list, 1);
	}
	return (1);
}

/*
**			nb_pages is on c_utils4.c
*/

int						put_options(t_c_tab *list, size_t val)
{
	size_t				a_page;

	MOVE_DOWN;
	if (val == 0)
		list->cursor = 0;
	else
		while (list && list->cursor != 1)
			list = list->next;
	if (!list)
		return (0);
	a_page = nb_pages(list);
	return (put_options_2(list, a_page, val));
}
