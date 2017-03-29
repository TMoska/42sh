/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_cursor_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 09:02:29 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/29 03:33:03 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_checkcurrentline(t_shell **shell)
{
	int i;

	i = ft_currentline(shell);
	if (i == 0)
		i = 1;
	return (i);
}

void			move_left(t_shell **shell)
{
	if ((*shell)->buff[(*shell)->term->tc_in - 1] == '\n')
	{
		(*shell)->term->tc_in -= 1;
		ft_putstr(tgetstr("up", NULL));
		if (ft_isfirstline(shell))
			ft_putstr(tgoto(tgetstr("ch", NULL), 0,
			ft_getpart(shell, NULL) + (*shell)->term->prompt_len - 1));
		else
		{
			(*shell)->term->tc_in += 1;
			ft_putstr(tgoto(tgetstr("ch", NULL), 0,
			ft_getpart(shell, NULL) - 1));
			(*shell)->term->tc_in -= 1;
		}
		return ;
	}
	if ((ft_isfirstline(shell) && ((*shell)->term->tc_in + (*shell)->term->
	prompt_len) % ft_linesize() == 0) || (!ft_isfirstline(shell) &&
	(ft_checkcurrentline(shell) % ft_linesize() == 0)))
		ft_put2str(tgetstr("up", NULL),
		tgoto(tgetstr("ch", NULL), 0, ft_linesize() - 1));
	else
		MOVE_LEFT;
	(*shell)->term->tc_in -= 1;
	return ;
}

void			move_right(t_shell **shell, char *buff, int offset)
{
	if ((*shell)->buff[(*shell)->term->tc_in] == '\n')
	{
		(*shell)->term->tc_in += 1;
		ft_put2str(tgetstr("do", NULL), tgoto(tgetstr("ch", NULL), 0, 0));
		return ;
	}
	if (offset == 0)
	{
		ft_put2str(tgetstr("im", NULL), buff);
		ft_putstr(tgetstr("ei", NULL));
		if ((ft_isfirstline(shell) && ((*shell)->term->tc_in + (*shell)->term->
		prompt_len) % ft_linesize() == 0) || (!ft_isfirstline(shell)
		&& (ft_checkcurrentline(shell) % ft_linesize() == 0)))
			ft_put2str(tgetstr("do", NULL), tgoto(tgetstr("ch", NULL), 0, 0));
		return ;
	}
	if ((ft_isfirstline(shell) && ((*shell)->term->tc_in + 1 + (*shell)->term->
	prompt_len) % ft_linesize() == 0) || (!ft_isfirstline(shell)
	&& (ft_checkcurrentline(shell) % ft_linesize() == 0)))
		ft_put2str(tgetstr("do", NULL), tgoto(tgetstr("ch", NULL), 0, 0));
	else
		ft_putstr(tgetstr("nd", NULL));
	if (offset)
		(*shell)->term->tc_in += 1;
}
