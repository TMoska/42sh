/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:40:56 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/30 17:31:31 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void**, size_t*))
{
  t_list *next;

  while (*alst)
  {
    next = (*alst)->next;
    ft_lstdelone(alst, del);
    *alst = next;
  }
}