/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:25:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 20:26:21 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_left(t_shell **shell, unsigned int key)
{
	int	i;

	i = (key == BTN_LEFT ? 1 : ((*shell)->tc_index));
	while ((i-- != 0))
	{
		MOVE_LEFT;
		((*shell)->tc_index -= 1);
	}
}

static void	move_right(t_shell **shell, unsigned int key)
{
	int	i;

	i = (key == BTN_RIGHT ? 1 : (*shell)->tc_len - (*shell)->tc_index);
	while ((i-- > 0))
	{
		MOVE_RIGHT;
		((*shell)->tc_index += 1);
	}
}

void		move_cursor_sides(t_shell **shell, unsigned int key)
{
	if (!(*shell)->buff)
		return ;
	if ((key == BTN_LEFT || key == BTN_HOME) && (*shell)->tc_index > 0)
		move_left(shell, key);
	else if ((key == BTN_RIGHT || key == BTN_END) &&
		(*shell)->tc_index < (*shell)->tc_len)
		move_right(shell, key);
}

void		move_cursor_alt(t_shell **shell, unsigned int key)
{
	
}