/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:29:48 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/28 01:15:05 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_buffer(t_shell **shell)
{
	ft_strdel(&(*shell)->buff);
	ft_putchar('\n');
	print_prompt(shell);
}

void	modify_buffer(t_shell **shell, unsigned int key)
{
	char	*tmp;

	if ((key == BTN_DEL && (*shell)->tc_in == (*shell)->tc_len) ||
		(key == BTN_BACK && (*shell)->tc_in == 0))
		return ;
	if (key == BTN_BACK)
	{
		MOVE_LEFT;
		((*shell)->tc_in -= 1);
	}
	DEL;
	(*shell)->tc_len -= 1;
	tmp = (*shell)->buff;
	(*shell)->buff = ft_strndelat((*shell)->buff,\
			(*shell)->tc_in, (size_t)1);
	ft_strdel(&tmp);
}
