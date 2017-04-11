/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 17:22:51 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/11 13:34:37 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					big_enough(t_c_tab *list)
{
	size_t largest;

	largest = 0;
	while (list)
	{
		if (largest < ft_strlen(list->name))
			largest = ft_strlen(list->name);
		list = list->next;
	}
	return ((size_t)ft_linesize() > largest);
}

struct s_pad		get_largest(struct s_pad pad, t_c_tab *list)
{
	size_t largest;

	largest = 0;
	while (list)
	{
		if (largest < ft_strlen(list->name))
			largest = ft_strlen(list->name);
		list = list->next;
	}
	pad.largest = largest + 1;
	return (pad);
}
