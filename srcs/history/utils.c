/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:09:26 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/05 14:56:20 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hist	*hist_new(char *cmd)
{
	t_hist *lst;
	size_t size;

	lst = (t_hist *)ft_memalloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	if (cmd)
	{
		size = ft_strlen(cmd);
		if ((lst->cmd = ft_strnew(size + 1)))
			ft_strcpy(lst->cmd, cmd);
		else
			return (NULL);
	}
	lst->next = NULL;
	return (lst);
}

void			rewind_history(t_hist **hist)
{
	while ((*hist) && (*hist)->prev)
		*hist = (*hist)->prev;
}

void			hist_add(t_hist **begin_list, char *cmd)
{
	t_hist *new;

	if (!(new = hist_new(cmd)))
		return ;
	rewind_history(begin_list);
	new->next = *begin_list;
	if (*begin_list)
		(*begin_list)->prev = new;
	*begin_list = new;
	rewind_history(begin_list);
}

void			print_history(t_shell **shell)
{
	t_hist *hist;

	hist = (*shell)->history;
	while (hist)
	{
		printf("%s\n", hist->cmd);
		hist = hist->next;
	}
}
