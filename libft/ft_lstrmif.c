/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:05:48 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 22:06:57 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstrmif(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = *begin_list;
	while (curr != NULL)
	{
		if (!(*cmp)(curr->content, data_ref))
		{
			if (prev == NULL)
				*begin_list = curr->next;
			else
				prev->next = curr->next;
			free(curr);
		}
		prev = curr;
		curr = curr->next;
	}
}
