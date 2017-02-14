/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 21:42:33 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 16:47:21 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap_nodes(void **one, void **two)
{
	void *tmp;

	tmp = *two;
	*two = *one;
	*one = tmp;
}

void			ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*tmp;
	int		sorted;

	if (!(*begin_list))
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *begin_list;
		while (tmp->next)
		{
			if (cmp(tmp->content, tmp->next->content) > 0)
			{
				sorted = 0;
				swap_nodes(&tmp->content, &tmp->next->content);
			}
			tmp = tmp->next;
		}
	}
}
