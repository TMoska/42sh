/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_removenode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:11:17 by moska             #+#    #+#             */
/*   Updated: 2017/01/26 17:55:50 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lst_removenode(t_list **begin_list, t_list *removable)
{
	t_list	*next;

	if (begin_list && *begin_list && removable)
	{
		if (*begin_list == removable)
		{
			next = (*begin_list)->next;
			ft_lstdelone(begin_list, &ft_lst_clear);
			*begin_list = next;
		}
		else
			ft_lst_removenode(&((*begin_list)->next), removable);
	}
}
