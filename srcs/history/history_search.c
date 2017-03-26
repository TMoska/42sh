/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 04:14:25 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 05:05:43 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*history_search_first_match(t_shell **shell, char *s)
{
	t_h_lst	*h_lst;

	h_lst = (*shell)->history->list;
	while (h_lst)
	{
		if (ft_strncmp(h_lst->cmd, s, ft_strlen(s)) == 0)
			return (h_lst->cmd);
		h_lst = h_lst->next;
	}
	return (NULL);
}
