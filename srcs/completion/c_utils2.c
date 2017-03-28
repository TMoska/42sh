/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/28 01:43:16 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static c_tab  *cmd_option_2(c_tab *tmp, char *cmd)
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

c_tab        *cmd_option(char *cmd, c_tab *list)
{
  c_tab     *tmp;
  c_tab     *prev;

  if (!list)
  {
    if (!(tmp = (c_tab*)malloc(sizeof(c_tab))))
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
    if (!(tmp = (c_tab*)malloc(sizeof(c_tab))))
      return (NULL);
    prev->next = tmp;
    tmp->prev = prev;
  }
  tmp = cmd_option_2(tmp, cmd);
  tmp->next = NULL;
  return (list);
}
