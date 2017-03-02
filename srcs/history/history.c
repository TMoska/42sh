/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:45:24 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/01 23:00:47 by moska            ###   ########.fr       */
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
	{
		// printf("1\n");
		(*shell)->hist_buff_tmp = ft_strdup((*shell)->buff);
	}
	else
	{
		// printf("2\n");
		(*shell)->history = (*shell)->history->next;
	}
	ft_strdel(&(*shell)->buff);
	return ((*shell)->history->cmd);
}

char	*find_prev_hist(t_shell **shell)
{
	char	*ret;

	ft_strdel(&(*shell)->buff);
	if (!(*shell)->history->prev)
	{
		ret = (*shell)->hist_buff_tmp;
		ft_strdel(&(*shell)->hist_buff_tmp);
	}
	else
	{
		(*shell)->history = (*shell)->history->prev;
		ret = (*shell)->history->cmd;
	}
	return (ret);
}

void		history(t_shell **shell, unsigned int key)
{
	if (!(*shell)->history)
		return ;
	if (key == BTN_UP)
	{
		if (!(*shell)->history->next && (*shell)->hist_buff_tmp)
			return ;
		clean_input(shell);
		work_buffer(shell, find_next_hist(shell));
	}
	else
	{
		if (!((*shell)->history || (*shell)->history->prev))
			return ;
		clean_input(shell);
		work_buffer(shell, find_prev_hist(shell));
	}
}