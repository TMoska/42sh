/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_lst_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:42:55 by ede-sous          #+#    #+#             */
/*   Updated: 2017/04/07 09:11:13 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		swap_nodes(char **one, char **two)
{
	char *tmp;

	tmp = *two;
	*two = *one;
	*one = tmp;
}

void			tab_lst_sort(t_c_tab **begin_list)
{
	t_c_tab		*tmp;
	int			sorted;

	if (!(*begin_list))
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *begin_list;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->content, tmp->next->content) > 0)
			{
				sorted = 0;
				swap_nodes(&tmp->content, &tmp->next->content);
			}
			tmp = tmp->next;
		}
	}
}
