/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:29:48 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/11 17:51:13 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		clean_buffer(t_shell **shell)
{
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = ft_strdup("\0");
	ft_putchar('\n');
	reset_line(shell);
	print_prompt(shell, NULL);
}

static int	buffer_bol(t_shell **shell)
{
	MOVE_LEFT;
	((*shell)->term->tc_in -= 1);
	return (1);
}

static void	delete_secondline(t_shell **shell)
{
	(*shell)->term->tc_in += 1;
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, ft_getpart(shell, NULL) - 1));
	(*shell)->term->tc_in -= 1;
}

void		modify_buffer(t_shell **shell, unsigned int key)
{
	char	*tmp;

	if ((key == BTN_DEL && (*shell)->term->tc_in == (*shell)->term->tc_len) ||
		(key == BTN_BACK && (*shell)->term->tc_in == 0))
		return ;
	key == BTN_BACK ? buffer_bol(shell) : 0;
	(*shell)->term->tc_len -= 1;
	tmp = (*shell)->buff;
	if ((*shell)->buff[(*shell)->term->tc_in] == '\n')
	{
		if (ft_isfirstline(shell))
			ft_putstr(tgoto(tgetstr("ch", NULL), 0,
			ft_getpart(shell, NULL) + (*shell)->term->prompt_len - 1));
		else
			delete_secondline(shell);
		(key == BTN_BACK) ? ft_putstr(tgetstr("up", NULL)) : (void)0;
	}
	(*shell)->buff = ft_strndelat((*shell)->buff,
			(*shell)->term->tc_in, (size_t)1);
	ft_printbuffer(shell);
	ft_strdel(&tmp);
}

void		cmd_rewrite(t_shell **shell)
{
	clear_cmdline(shell);
	ft_putstr((*shell)->buff);
	(*shell)->term->tc_in = (*shell)->term->tc_len;
}
