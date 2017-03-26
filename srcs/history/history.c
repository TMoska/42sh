/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:45:24 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 10:36:57 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_hist_of_index(t_shell **shell, int index, int e_m)
{
	t_h_lst	*lst;

	ft_strdel(&(*shell)->buff);
	if (index == -1 && e_m == 0)
		return ;
	lst = (*shell)->history->list;
	while (lst->index != index)
		lst = lst->next;
	work_buffer(shell, lst->cmd);
}

void			clean_input(t_shell **shell)
{
	int i;

	i = 0;
	CURS_LEFT;
	while (i < (*shell)->term->prompt_len)
	{
		MOVE_RIGHT;
		i++;
	}
	//DEL_LINE;
	//reset_line(shell);
	clear_cmdline(shell);
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
	clean_input(shell);
	(key == BTN_UP) ? find_next_hist(shell) : find_prev_hist(shell);
	set_hist_of_index(shell, (*shell)->history->at_index, 0);
}
