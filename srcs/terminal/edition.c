/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:12:13 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/11 18:06:46 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_space(t_shell **shell)
{
	if (ft_isfirstline(shell) &&
			((ft_currentline(shell) + (*shell)->term->prompt_len)
			% (ft_linesize()) == 0))
	{
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	else if (!ft_isfirstline(shell) &&
			(ft_currentline(shell) % (ft_linesize()) == 0))
	{
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	else if (!ft_isfirstline(shell) && ft_currentline(shell) > ft_linesize() &&
			((ft_currentline(shell) + 1) % (ft_linesize()) == 0))
	{
		ft_putchar(' ');
		ft_putchar(' ');
	}
}

void	clear_cmdline(t_shell **shell)
{
	int i;

	i = 0;
	back_to_prompt(shell, 1);
	ft_putstr(tgoto(tgetstr("ch", NULL), 0,
				(*shell)->term->prompt_len));
	ft_putstr(tgetstr("cd", NULL));
}

void	goto_endcmdline(t_shell **shell)
{
	while ((*shell)->term->tc_in < (*shell)->term->tc_len)
		move_right(shell, NULL, 1);
}

void	back_to_prompt(t_shell **shell, int keep)
{
	int line;

	line = (*shell)->term->tc_in;
	if ((*shell)->term->tc_len == 0)
	{
		(*shell)->term->tc_in = 0;
		return ;
	}
	while ((*shell)->term->tc_in != 0)
		move_left(shell);
	if (keep == 1)
		(*shell)->term->tc_in = line;
}

void	ft_printbuffer(t_shell **shell)
{
	int i;

	i = (*shell)->term->tc_in;
	ft_putstr(tgetstr("vi", NULL));
	ft_putstr(tgetstr("cd", NULL));
	while ((*shell)->term->tc_in != (*shell)->term->tc_len)
		ft_putchar((*shell)->buff[(*shell)->term->tc_in++]);
	ft_putstr(tgetstr("ve", NULL));
	put_space(shell);
	while ((*shell)->term->tc_in != i)
		move_left(shell);
}
