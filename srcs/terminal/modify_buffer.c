/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:29:48 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/28 19:43:49 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_buffer(t_shell **shell)
{
	ft_strdel(&(*shell)->buff);
	ft_putchar('\n');
	reset_line(shell);
	print_prompt(shell, NULL);
}

void	modify_buffer(t_shell **shell, unsigned int key)
{
	char	*tmp;

	if ((key == BTN_DEL && (*shell)->term->tc_in == (*shell)->term->tc_len) ||
		(key == BTN_BACK && (*shell)->term->tc_in == 0))
		return ;
	if (key == BTN_BACK)
	{
		MOVE_LEFT;
		((*shell)->term->tc_in -= 1);
	}
	(*shell)->term->tc_len -= 1;
	tmp = (*shell)->buff;
	if ((*shell)->buff[(*shell)->term->tc_in] == '\n')
	{
		if (ft_isfirstline(shell))
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_getpart(shell)) + (*shell)->term->prompt_len - 1));
		else
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_getpart(shell)) - 1));
		ft_putstr(tgetstr("up", NULL));
	}
	(*shell)->buff = ft_strndelat((*shell)->buff,\
			(*shell)->term->tc_in, (size_t)1);
	ft_printbuffer(shell);
	ft_strdel(&tmp);
}
