/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 21:39:44 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 21:42:23 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **begin_list)
{
	t_list	*back;
	t_list	*forward;

	back = 0;
	forward = *begin_list;
	while (forward)
	{
		forward = (*begin_list)->next;
		if (back)
			(*begin_list)->next = back;
		else
			(*begin_list)->next = 0;
		back = *begin_list;
		(*begin_list) = forward;
	}
	*begin_list = back;
}
