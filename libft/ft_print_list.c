/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 02:38:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 03:02:01 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_list *lst)
{
	t_list *l;

	l = lst;
	ft_putendl("=========================");
	ft_putendl("START ft_print_list START");
	while (l)
	{
		ft_putendl(l->content);
		l = l->next;
	}
	ft_putendl("  END ft_print_list END  ");
	ft_putendl("=========================");
}
