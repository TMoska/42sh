/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 19:37:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/27 16:56:30 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		write_buffer(t_shell **shell, char *buffer)
{
	char	*tmp;

	(*shell)->tc_index += 1;
	(*shell)->tc_len += 1;
	if (!(*shell)->buff && ((*shell)->buff = ft_strdup(buffer)))
		return ;
	tmp = (*shell)->buff;
	(*shell)->buff = ft_strjoin((*shell)->buff, buffer);
	ft_strdel(&tmp);
}

void	work_buffer(t_shell **shell, char *buffer)
{
	write_buffer(shell, buffer);
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(buffer);
	ft_putstr(tgetstr("ei", NULL));
}

static int	identify_key(t_shell **shell, char *buffer, unsigned int key)
{
	if (key != BTN_ENTER && ft_isprint(key))
		work_buffer(shell, buffer);
	else if (key == BTN_LEFT || key == BTN_RIGHT ||
		key == BTN_END || key == BTN_HOME)
		move_cursor_sides(shell, key);
	else if (key == BTN_BACK || key == BTN_DEL)
		modify_buffer(shell, key);
	else if (key == BTN_CTRL_D)
		sig_callback(SIGQUIT);
	if (key == BTN_ENTER)
	{
		(*shell)->tc_index = 0;
		(*shell)->tc_len = 0;
		return (0);
	}
	return (1);
}

void		read_input(t_shell **shell)
{
	char	*buffer[5];

	ft_memset(buffer, 0, 5);
	while ((read(0, buffer, 5)) > 0 &&
		identify_key(shell, (char *)buffer, (unsigned int)*buffer))
		ft_memset(buffer, 0, 5);
	ft_putchar('\n');
}