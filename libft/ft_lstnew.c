/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:13:14 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/24 16:37:49 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = (t_list *)ft_memalloc(sizeof(*list));
	if (!list)
		return (NULL);
	if (content)
	{
		if ((list->content = ft_memalloc(content_size)))
			ft_memcpy(list->content, content, content_size);
		else
			return (NULL);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}
