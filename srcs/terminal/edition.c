/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:12:13 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/31 04:24:40 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmdline(t_shell **shell)
{
	int i;

	i = 0;
	ft_putstr(tgetstr("sc", NULL));
	back_to_prompt(shell, 1);
	ft_putstr(tgoto(tgetstr("ch", NULL), 0,
	(*shell)->term->prompt_len));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(tgetstr("rc", NULL));
	back_to_prompt(shell, 0);
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
	while ((*shell)->term->tc_in > 0)
		move_left(shell);
	if (keep == 1)
		(*shell)->term->tc_in = line;
}

void	ft_printbuffer(t_shell **shell)
{
	int i;

	i = (*shell)->term->tc_in;
	ft_putstr(tgetstr("vi", NULL));
	ft_putstr(tgetstr("sc", NULL));
	clear_cmdline(shell);
	ft_putstr((*shell)->buff);
	ft_putchar(' ');
	ft_putstr(tgetstr("rc", NULL));
	ft_putstr(tgetstr("ve", NULL));
	(*shell)->term->tc_in = i;
}
