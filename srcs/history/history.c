/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 11:06:18 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/05 02:46:32 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_hist_of_index(t_shell **shell, int index)
{
	t_h_lst	*lst;

	ft_strdel(&(*shell)->buff);
	if (index == -1)
		return ;
	lst = hist_at_index(shell, index);
	work_buffer(shell, lst->cmd);
}

static void		find_next_hist(t_shell **shell)
{
	if ((*shell)->history->at_index == -1)
		(*shell)->history->at_index = (*shell)->history->size - 1;
	else
		(*shell)->history->at_index--;
}

static void		find_prev_hist(t_shell **shell)
{
	if ((*shell)->history->at_index == (*shell)->history->size - 1)
		(*shell)->history->at_index = -1;
	else
		(*shell)->history->at_index++;
}

void			history(t_shell **shell, unsigned int key)
{
	t_hist	*h;

	h = (*shell)->history;
	if (!h->list ||
	(key == BTN_UP && h->at_index == 0) ||
	(key == BTN_DOWN && (h->at_index == -1)))
		return ;
	clear_cmdline(shell);
	reset_line(shell);
	(key == BTN_UP) ? find_next_hist(shell) : find_prev_hist(shell);
	set_hist_of_index(shell, (*shell)->history->at_index);
}
