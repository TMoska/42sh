/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 00:38:15 by moska             #+#    #+#             */
/*   Updated: 2017/01/30 17:31:10 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lst_remove_if(t_list **begin_list, void *content, int (*cmp)())
{
	t_list *tmp;
	t_list *prev;

	tmp = *begin_list;
	prev = NULL;
	while (!cmp(tmp->content, content) && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (cmp(tmp->content, content))
	{
		if (prev)
			prev->next = tmp->next;
		else
			*begin_list = tmp->next;
		ft_lstdelone(&tmp, &ft_lst_clear);
	}
}
