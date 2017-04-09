/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_arrows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/09 17:51:29 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			arrow_up(t_c_tab **tmp)
{
	size_t			c_col;

	c_col = (*tmp)->col;
	if ((*tmp)->prev && (*tmp)->prev->col == c_col)
	{
		(*tmp)->cursor = 0;
		(*tmp) = (*tmp)->prev;
		(*tmp)->cursor = 1;
	}
}

static void			arrow_down(t_c_tab **tmp)
{
	size_t			c_col;

	c_col = (*tmp)->col;
	if ((*tmp)->next && (*tmp)->next->col == c_col)
	{
		(*tmp)->cursor = 0;
		(*tmp) = (*tmp)->next;
		(*tmp)->cursor = 1;
	}
}

/*
**			For both init_*arrow* functions go to c_utils3.c
*/

static void			arrow_right(t_c_tab **tmp)
{
	size_t			c;
	size_t			l;
	size_t			page;
	t_c_tab			*lst;

	if (!(tmp = init_right(tmp, &c, &l, &page)))
		return ;
	if (!(*tmp)->next && c == (*tmp)->col && c != 1 && ((*tmp)->cursor = 1))
		return ;
	lst = *tmp;
	while ((*tmp)->next && ((*tmp)->col != c || (*tmp)->place != l))
		(*tmp) = (*tmp)->next;
	if ((*tmp)->col == c || (*tmp)->place == l)
		if (lst->next)
		{
			(*tmp)->cursor = 1;
			return ;
		}
	if (!(*tmp)->next && page == (*tmp)->page)
		while ((*tmp)->prev && ((*tmp)->page != 1 || (*tmp)->col != 1
					|| (*tmp)->place != l))
			(*tmp) = (*tmp)->prev;
	(*tmp)->cursor = 1;
}

static void			arrow_left(t_c_tab **tmp)
{
	size_t			c;
	size_t			l;
	size_t			page;

	if (!(tmp = init_left(tmp, &c, &l, &page)))
		return ;
	if (c == 0)
	{
		if ((*tmp)->page == 1 && (*tmp)->next && ((*tmp) = (*tmp)->next))
		{
			while ((*tmp)->next)
				(*tmp) = (*tmp)->next;
			if (l < (*tmp)->place)
				while ((*tmp)->prev && (*tmp)->place != l)
					(*tmp) = (*tmp)->prev;
		}
		else if (((*tmp) = (*tmp)->prev))
			while ((*tmp)->prev && (*tmp)->place != l)
				(*tmp) = (*tmp)->prev;
	}
	else if (((*tmp) = (*tmp)->prev))
		while ((*tmp)->prev && (*tmp)->place != l)
			(*tmp) = (*tmp)->prev;
	(*tmp)->cursor = 1;
}

t_c_tab				*move_select(t_c_tab *list, size_t val)
{
	t_c_tab			*tmp;

	tmp = list;
	while (tmp->next && tmp->cursor != 1)
		tmp = tmp->next;
	if (val == 9)
	{
		tmp->cursor = 0;
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = list;
		tmp->cursor = 1;
	}
	else if (val == 8)
		arrow_up(&tmp);
	else if (val == 6)
		arrow_right(&tmp);
	else if (val == 4)
		arrow_left(&tmp);
	else if (val == 2)
		arrow_down(&tmp);
	return (list);
}
