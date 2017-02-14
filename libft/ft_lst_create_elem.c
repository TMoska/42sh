/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_create_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:56:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 16:50:07 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lst_create_elem(void *data)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	new_list->content = data;
	new_list->next = NULL;
	return (new_list);
}
