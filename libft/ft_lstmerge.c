/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:00:59 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 22:03:04 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmerge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *l;

	l = *begin_list1;
	if (!(*begin_list1) || !begin_list2)
		return ;
	while ((*begin_list1)->next != NULL)
		*begin_list1 = (*begin_list1)->next;
	(*begin_list1)->next = begin_list2;
	*begin_list1 = l;
}
