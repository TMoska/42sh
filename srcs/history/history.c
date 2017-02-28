/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:45:24 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/28 18:35:42 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		clean_input(t_shell **shell)
{
	int i;

	i = 0;
	CURS_LEFT;
	while (i < (*shell)->prompt_len)
	{
		MOVE_RIGHT
		i++;
	}
	DEL_LINE;
	reset_line(shell);
}

char	*find_next_hist(t_shell **shell)
{
	if (!(*shell)->hist_buff_tmp)
		(*shell)->hist_buff_tmp = ft_strdup((*shell)->buff);
	else
		(*shell)->history = (*shell)->history->next;
	ft_strdel(&(*shell)->buff);
	return ((*shell)->history->cmd);
}

void		history(t_shell **shell, unsigned int key)
{
	if (!(*shell)->history)
		return ;
	if (key == BTN_UP)
	{
		if (!(*shell)->history->next)
			return ;
		clean_input(shell);
		work_buffer(shell, find_next_hist(shell));
	}
	else
	{
		if (!((*shell)->history || (*shell)->history->prev))
			return ;
	// 	clean_input(shell);
	// 	ft_strdel(&(*shell)->buff);
	// 	work_buffer(shell, (*shell)->history->cmd);
	}
}