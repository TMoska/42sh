/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:00:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/30 04:46:19 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cut_to_buff(t_shell **shell, int from, int size, char **tmp)
{
	*tmp = ft_strndelat((*shell)->buff, from, size);
	(*shell)->clipboard = ft_strndup(&(*shell)->buff[from], size);
}

void		cut_line(t_shell **shell, unsigned int key)
{
	char	*tmp;
	char	*tmp1;

	tmp = (*shell)->buff;
	tmp1 = (*shell)->clipboard;
	if (key == BTN_CTRL_K)
		cut_to_buff(shell, 0, (*shell)->term->tc_in, &tmp);
	else
		cut_to_buff(shell, (*shell)->term->tc_in,\
					(*shell)->term->tc_len - (*shell)->term->tc_in, &tmp);
	while ((*shell)->term->tc_in)
		move_left(shell);
	ft_strdel(&(*shell)->buff);
	reset_line(shell);
	work_buffer(shell, tmp);
	move_cursor_sides(shell, (key == BTN_CTRL_K) ? BTN_HOME : BTN_END);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
}

void		copy(t_shell **shell)
{
	char	*tmp;

	tmp = (*shell)->clipboard;
	(*shell)->clipboard = ft_strdup((*shell)->buff);
	ft_strdel(&tmp);
}
