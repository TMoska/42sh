/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/03/28 04:35:29 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static c_tab  *move_select(c_tab *list, size_t val)
{
  c_tab       *tmp;

  tmp = list;
  while (tmp->next && tmp->cursor != 1)
    tmp = tmp->next;
    (void)val;
  return (list);
}

/*static size_t  verify_btn(unsigned int key)
{
  if (key == BTN_UP)
    return (8);
  else if (key == BTN_RIGHT || key == BTN_TAB)
    return (6);
  else if (key == BTN_LEFT)
    return (4);
  else if (key == BTN_DOWN)
    return (2);
  else if (key != BTN_ENTER || key != BTN_SPACE)
    return (9);
  return (0);
}*/

void    tab_completion(t_shell **shell, c_tab *list, size_t val)
{
  char    *path;
  char    **paths;
  size_t  i;

  i = -1;
  if (val != 0 && list)
    list = move_select(list, val);
  else if (binary_directories(*shell))
  {
    if (!(path = get_env_val(shell, "PATH")))
        return ;
    if (!path || !(paths = ft_strsplit(path, ':')))
      return ;
    while (paths[++i])
      list = search_on_dir(paths[i], *shell, list);
      if (!list)
      return ;
  }
  else if (!(list = search_on_dir(".", *shell, NULL)))
    return ;
 if (val == 0)
        if (!(list = define_pading(list, *shell)))
            return ;
    while (list)
    {
        ft_putendl(list->content);
        if (!list->next)
            break ;
        list = list->next;
    }
  /*if (put_options(list, &*shell) == 0)
      return ;
  read(0, buff, 2);
  if ((*shell)->buff && (val = verify_btn((unsigned int)(*shell)->buff)) != 9)
      tab_completion(shell, list, val);
  // Erase list, i don't know how to do it :x -> have to put it on 25lines
  MOVE_DOWN;
  DEL_LINES;
  MOVE_UP;*/
}
