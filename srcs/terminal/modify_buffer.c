/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:29:48 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/26 11:03:58 by adeletan         ###   ########.fr       */
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
	(*shell)->buff = ft_strndelat((*shell)->buff,\
			(*shell)->term->tc_in, (size_t)1);
	ft_printbuffer(shell);
	ft_strdel(&tmp);
}
