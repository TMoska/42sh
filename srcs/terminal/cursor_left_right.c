/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:25:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/28 11:25:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_left(t_shell **shell)
{
	MOVE_LEFT;
	((*shell)->tc_in -= 1);
}

static void	move_right(t_shell **shell)
{
	MOVE_RIGHT;
	((*shell)->tc_in += 1);
}

void		move_cursor_sides(t_shell **shell, unsigned int key)
{
	int		i;

	if (!(*shell)->buff)
		return ;
	if ((key == BTN_LEFT || key == BTN_HOME) && (*shell)->tc_in > 0)
	{
		i = (key == BTN_LEFT ? 1 : ((*shell)->tc_in));
		while ((i-- != 0))
			move_left(shell);
	}
	else if ((key == BTN_RIGHT || key == BTN_END) &&
		(*shell)->tc_in < (*shell)->tc_len)
	{
		i = (key == BTN_RIGHT ? 1 : (*shell)->tc_len - (*shell)->tc_in);
		while ((i-- > 0))
			move_right(shell);
	}
}

void		move_cursor_alt(t_shell **s, unsigned int key)
{
	if (((*s)->tc_in == 0 && key == BTN_ALEFT) ||
		((*s)->tc_in == 1 && key == BTN_ARIGHT))
		return ;
	if (key == BTN_ALEFT)
	{
		if ((*s)->buff[(*s)->tc_in - 1] == ' ')
			move_left(s);
		if ((*s)->buff[(*s)->tc_in] == ' ')
			move_left(s);
		while (!((*s)->buff[(*s)->tc_in] == ' ' || (*s)->tc_in == 0))
			move_left(s);
		if ((*s)->buff[(*s)->tc_in] == ' ' && (*s)->tc_in != 0)
			move_right(s);
	}
	else
	{
		if ((*s)->buff[(*s)->tc_in] == ' ')
			move_right(s);
		while ((!((*s)->buff[(*s)->tc_in] == ' ' ||
			(*s)->tc_in == (*s)->tc_len)))
			move_right(s);
	}
}
