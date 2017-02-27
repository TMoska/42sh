/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:25:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 23:29:20 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_left(t_shell **shell)
{
	MOVE_LEFT;
	((*shell)->tc_index -= 1);
}

static void	move_right(t_shell **shell)
{
	MOVE_RIGHT;
	((*shell)->tc_index += 1);
}

void		move_cursor_sides(t_shell **shell, unsigned int key)
{
	int		i;

	if (!(*shell)->buff)
		return ;
	if ((key == BTN_LEFT || key == BTN_HOME) && (*shell)->tc_index > 0)
	{
		i = (key == BTN_LEFT ? 1 : ((*shell)->tc_index));
		while ((i-- != 0))
			move_left(shell);

	}
	else if ((key == BTN_RIGHT || key == BTN_END) &&
		(*shell)->tc_index < (*shell)->tc_len)
	{
		i = (key == BTN_RIGHT ? 1 : (*shell)->tc_len - (*shell)->tc_index);
		while ((i-- > 0))
			move_right(shell);
	}
}

void		move_cursor_alt(t_shell **shell, unsigned int key)
{
	char	*b;
	int 	in;
	int		l;

	in = (*shell)->tc_index;
	b = (*shell)->buff;
	l = (*shell)->tc_len;
	if (key == BTN_ALEFT)
	{
		if (in == 0)
			return ;
		if ((*shell)->buff[in - 1] == ' ' && (in -= 1))
			move_left(shell);
		if (((*shell)->buff[in] == ' ') && (in -= 1))
			move_left(shell);
		while (!((*shell)->buff[in] == ' ' || in == 0) && (in -= 1))
			move_left(shell);
		if ((*shell)->buff[in] == ' ' && (in += 1))
			move_right(shell);
	}
	else
	{
		if (in == l)
			return ;
		if (b[in] == ' ')
		{
			move_right(shell);
			in += 1;
		}
		while (!(b[in] == ' ' || in == l))
		{
			move_right(shell);
			in += 1;
		}
	}
}