/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_add_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 02:28:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 02:58:48 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lst_new_add_back(t_list **alst, void const *content,\
	 	size_t size)
{
	t_list	*new;

	if (!(new = ft_lstnew(content, size + 1)) || ft_lstadd_back(alst, new))
		return (1);
	return (0);
}
