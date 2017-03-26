/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:25:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 09:55:17 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	move_left(t_shell **shell)
{
	MOVE_LEFT;
	((*shell)->term->tc_in -= 1);
}
*/
/*
static void	move_right(t_shell **shell)
{
	MOVE_RIGHT;
	((*shell)->term->tc_in += 1);
}
*/
void		move_cursor_sides(t_shell **shell, unsigned int key)
{
	int		i;

	if (!(*shell)->buff)
		return ;
	if ((key == BTN_LEFT || key == BTN_HOME) && (*shell)->term->tc_in > 0)
	{
		i = (key == BTN_LEFT ? 1 : ((*shell)->term->tc_in));
		while ((i-- != 0))
			move_left(shell);
	}
	else if ((key == BTN_RIGHT || key == BTN_END) &&
		(*shell)->term->tc_in < (*shell)->term->tc_len)
	{
		i = (key == BTN_RIGHT ? 1 : (*shell)->term->tc_len -
			(*shell)->term->tc_in);
		while ((i-- > 0))
			move_right(shell, NULL, 1);
	}
}

void		move_cursor_alt(t_shell **s, unsigned int key)
{
	if (((*s)->term->tc_in == 0 && key == BTN_ALEFT) ||
		((*s)->term->tc_in == 1 && key == BTN_ARIGHT))
		return ;
	if (key == BTN_ALEFT)
	{
		if ((*s)->buff[(*s)->term->tc_in - 1] == ' ')
			move_left(s);
		if ((*s)->buff[(*s)->term->tc_in] == ' ')
			move_left(s);
		while (!((*s)->buff[(*s)->term->tc_in] == ' ' ||
			(*s)->term->tc_in == 0))
			move_left(s);
		if ((*s)->buff[(*s)->term->tc_in] == ' ' && (*s)->term->tc_in != 0)
			move_right(s, NULL, 1);
	}
	else
	{
		if ((*s)->buff[(*s)->term->tc_in] == ' ')
			move_right(s, NULL, 1);
		while ((!((*s)->buff[(*s)->term->tc_in] == ' ' ||
			(*s)->term->tc_in == (*s)->term->tc_len)))
			move_right(s, NULL, 1);
	}
}
