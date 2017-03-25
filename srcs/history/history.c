/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:45:24 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 21:51:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clean_input(t_shell **shell)
{
	int i;

	i = 0;
	CURS_LEFT;
	while (i < (*shell)->prompt_len)
	{
		MOVE_RIGHT;
		i++;
	}
	DEL_LINE;
	reset_line(shell);
}
//
// static void		find_next_hist(t_shell **shell)
// {
// 	if (!(*shell)->hist_buff_tmp && (*shell)->buff)
// 		(*shell)->hist_buff_tmp = ft_strdup((*shell)->buff);
// 	else if ((*shell)->hist_buff_tmp)
// 		(*shell)->history = (*shell)->history->next;
// 	ft_strdel(&(*shell)->buff);
// 	work_buffer(shell, (*shell)->history->cmd);
// }
//
// static void		find_prev_hist(t_shell **shell)
// {
// 	char	*ret;
//
// 	ft_strdel(&(*shell)->buff);
// 	if (!(*shell)->history->prev)
// 	{
// 		ret = (*shell)->hist_buff_tmp;
// 		ft_strdel(&(*shell)->hist_buff_tmp);
// 	}
// 	else
// 	{
// 		(*shell)->history = (*shell)->history->prev;
// 		ret = (*shell)->history->cmd;
// 	}
// 	work_buffer(shell, ret);
// }
//
void			history(t_shell **shell, unsigned int key)
{
	(void)shell;
	(void)key;
	// if (!(*shell)->history ||
	// (key == BTN_UP && (!(*shell)->history->next && (*shell)->hist_buff_tmp)) ||
	// (key == BTN_DOWN && !((*shell)->history || (*shell)->history->prev)))
	// 	return ;
	// clean_input(shell);
	// (key == BTN_UP) ? find_next_hist(shell) : find_prev_hist(shell);
}
