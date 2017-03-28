/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_cursor_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 09:02:29 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/28 19:37:32 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_left(t_shell **shell)
{
	if ((*shell)->buff[(*shell)->term->tc_in - 1] == '\n')
	{
		(*shell)->term->tc_in -= 1;
		ft_putstr(tgetstr("up", NULL));
		if (ft_isfirstline(shell))
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_getpart(shell)) + (*shell)->term->prompt_len - 1));
		else
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_getpart(shell)) - 1));
		return ;
	}
	if ((ft_currentline(shell) + (*shell)->term->prompt_len) %
		ft_linesize() == 0)
	{
		ft_putstr(tgetstr("up", NULL));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_linesize() - 1));
	}
	else
		MOVE_LEFT;
	(*shell)->term->tc_in -= 1;
	return ;
}

void	move_right(t_shell **shell, char *buff, int offset)
{
	if ((*shell)->buff[(*shell)->term->tc_in] == '\n')
	{
		(*shell)->term->tc_in += 1;
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		return ;
	}
	if (offset == 0)
	{
		ft_putstr(tgetstr("im", NULL));
		ft_putstr(buff);
		ft_putstr(tgetstr("ei", NULL));
	if ((ft_currentline(shell) + (*shell)->term->prompt_len) % ft_linesize() == 0)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	}
		return ;
	}
	if ((ft_currentline(shell) + (*shell)->term->prompt_len + 1) % ft_linesize() == 0)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	}
	else
		ft_putstr(tgetstr("nd", NULL));
	if (offset)
		(*shell)->term->tc_in += 1;
}
