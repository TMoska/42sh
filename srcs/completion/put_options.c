/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/28 01:49:32 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    option_prompt(c_tab *list, t_shell **shell)
{
  while (list && list->cursor != 1)
    list = list->next;
  ft_strdel(&((*shell)->buff));
  (*shell)->buff = ft_strdup(list->content);
  clear_cmdline(shell);
  work_buffer(shell, NULL);
}

static void			put_2_page(c_tab *list)
{
	if (list->cursor == 0)
		ft_putstr(list->content);
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
    p.c_line = 1;
		p.m_len = 0;
		while (list && list->col == p.c_col)
		{
            ft_putstr(tgoto(tgetstr("ch", NULL), 0, p.max_len));
			p.c_line++;
			p.len = ft_strlen(list->content);
			(p.len > p.m_len ? p.m_len = p.len : p.m_len);
			put_2_page(list);
			list = list->next;
            MOVE_DOWN;
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
    while (list && list->cursor != 1)
      list = list->next;
    if (!list)
      return (0);
    c_page = list->page;
    while (list->prev && list->page == c_page)
      list = list->prev;
    (list->prev ? list = list->next : list);
    put_page(list, c_page);
    option_prompt(list, &*shell);
    return (1);
}
