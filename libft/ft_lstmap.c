/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:54:49 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 14:05:44 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*n_lst;
	t_list	*nw_lst;

	if (!lst || !(*f))
		return (0);
	if (!(n_lst = (*f)(lst)))
		return (0);
	nw_lst = n_lst;
	while (lst->next)
	{
		lst = lst->next;
		nw_lst->next = (*f)(lst);
		if (!nw_lst->next)
			return (0);
		nw_lst = nw_lst->next;
	}
	return (n_lst);
}
