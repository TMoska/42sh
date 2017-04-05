/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:25:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/04 04:58:28 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isspace((*s)->buff[(*s)->term->tc_in - 1])
			&& (*s)->term->tc_in != 0)
			move_left(s);
		while (ft_isspace((*s)->buff[(*s)->term->tc_in])
			&& (*s)->term->tc_in != 0)
			move_left(s);
		while (!(ft_isspace((*s)->buff[(*s)->term->tc_in - 1]) ||
			(*s)->term->tc_in == 0))
			move_left(s);
	}
	else
	{
		while (ft_isspace((*s)->buff[(*s)->term->tc_in]))
			move_right(s, NULL, 1);
		while (!((ft_isspace((*s)->buff[(*s)->term->tc_in]) ||
			(*s)->term->tc_in == (*s)->term->tc_len)))
			move_right(s, NULL, 1);
	}
}
