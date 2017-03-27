/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/26 12:48:24 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    option_prompt(c_tab *list, t_shell **shell)
{
  while (list && list->cursor != 1)
    list->next;
  ft_strdel(&((*shell)->buff));
  (*shell)->buff = ft_strdup(list->content);

  work_buffer(&*shell, NULL);
}

static void			put_2_page(c_tab *list)
{
	if (list->cursor == 0)
		ft_putstr(list->content, 0);
  else
  {
    ft_putstr("\033[7;92m");
    ft_putstr(list->content);
    ft_putstr("\033[0m");
  }
}

static void put_page(c_tab *list, size_t c_page)
{
  struct    p_put p;

  p.max_len = 0;
  p.c_col = 1;
  while (list && list->page == c_page)
  {
    SAVE_LINE;
    MOVE_DOWN;
    p.c_line = 1;
		p.m_len = 0;
		while (list && list->col == p.c_col)
		{
			DOWN;
      ft_putstr(tgoto(tgetstr("ch", NULL), 0, p.max_line));
			p.c_line++;
			p.len = ft_strlen(list->content);
			(p.len > p.m_len ? p.m_len = p.len : p.m_len);
			put_2_page(list);
			list = list->next;
		}
    LOAD_LINE;
		p.max_len += p.m_len + 3;
		p.c_col++;
  }
}

int         put_options(c_tab *list, t_shell **shell)
{
    size_t  c_page;

    MOVE_DOWN;
    DEL_LINES;
    MOVE_UP;
    if (!(list = define_padding(list)))
        return (0);
    while (list && list->cursor != 1)
      list = list->next;
    if (!list)
      return (0);
    c_page = tmp->page;
    while (tmp->prev && tmp->page == c_page)
      tmp = tmp->prev;
    (tmp->prev ? tmp = tmp->next : tmp);
    put_page(list, c_page);
    option_prompt(list, &*shell);
}
