/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 12:35:39 by moska             #+#    #+#             */
/*   Updated: 2017/01/22 12:36:05 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int   ft_lstadd_back(t_list **alst, t_list *new)
{
  t_list  *tmp;

  tmp = *alst;
  if (!new)
    return (0);
  if (*alst)
  {
    while (tmp->next)
      tmp = tmp->next;
    tmp->next = new;
  }
  else
    ft_lstadd(alst, new);
  return (1);
}
