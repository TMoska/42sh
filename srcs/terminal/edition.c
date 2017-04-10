/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:12:13 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/10 05:26:31 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cmd_rewrite(t_shell **shell)
{
	clear_cmdline(shell);
	ft_putstr((*shell)->buff);
	(*shell)->term->tc_in = (*shell)->term->tc_len;
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
	int i2;

	i = (*shell)->term->tc_in;
	i2 = (*shell)->term->tc_in;
	ft_putstr(tgetstr("vi", NULL));
	clear_cmdline(shell);
	(*shell)->term->tc_in = i;
	i = 0;
	while (i < (*shell)->term->tc_in)
		ft_putchar((*shell)->buff[i++]);
	if (!ft_isfirstline(shell) && (ft_getpart(shell, NULL) %
		(ft_linesize() + 1) == 0))
	{
		ft_putchar(' ');
	}
	while (i < (*shell)->term->tc_len)
		ft_putchar((*shell)->buff[i++]);
	(*shell)->term->tc_in = (*shell)->term->tc_len;
	while ((*shell)->term->tc_in != i2)
		move_left(shell);
	ft_putstr(tgetstr("ve", NULL));
}
