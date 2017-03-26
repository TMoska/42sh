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

int         put_options(c_tab *list)
{
    size_t  c_page;

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
    MOVE_DOWN;
}
