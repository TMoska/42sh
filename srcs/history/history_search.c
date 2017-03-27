/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 04:14:25 by moska             #+#    #+#             */
/*   Updated: 2017/03/26 15:23:02 by moska            ###   ########.fr       */
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

char	*history_search_first_arg_match(t_shell **shell, char *s)
{
	t_h_lst	*h_lst;
	char	*cmpr;
	int		i;

	h_lst = (*shell)->history->list;
	while (h_lst)
	{
		i = 0;
		while (!(h_lst->cmd[i] == ' ' || h_lst->cmd[i] == '\0'))
			i++;
		cmpr = &h_lst->cmd[i + 1];
		if (ft_strncmp(cmpr, s, ft_strlen(s)))
			return (&h_lst->cmd[i]);
		h_lst = h_lst->next;
	}
	return (NULL);
}
