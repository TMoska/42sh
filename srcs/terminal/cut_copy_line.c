/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:00:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 03:39:13 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cut_line(t_shell **shell, unsigned int key)
{
	char	*tmp;
	char	*tmp1;

	tmp = (*shell)->buff;
	tmp1 = (*shell)->clipboard;
	if (key == BTN_CTRL_K)
	{
		tmp = ft_strndelat((*shell)->buff, 0, (*shell)->term->tc_in);
		(*shell)->clipboard = ft_strndup((*shell)->buff,
				(*shell)->term->tc_in);
	}
	else
	{
		tmp = ft_strndelat((*shell)->buff, (*shell)->term->tc_in,\
			(*shell)->term->tc_len - (*shell)->term->tc_in);
		(*shell)->clipboard = ft_strndup(&(*shell)->buff[(*shell)->term->
			tc_in], (*shell)->term->tc_len - (*shell)->term->tc_in);
	}
	clean_input(shell);
	ft_strdel(&(*shell)->buff);
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
