/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 17:22:51 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/09 17:31:47 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	pad.largest = largest;
	return (pad);
}
