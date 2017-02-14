/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_in_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 21:14:26 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/21 14:49:31 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_in_list(t_list *begin_list, void *data, int (*cmp)())
{
	while (begin_list)
	{
		if (cmp(begin_list->content, data))
			return (1);
		begin_list = begin_list->next;
	}
	return (0);
}
