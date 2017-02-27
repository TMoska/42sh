/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 19:37:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/27 19:32:16 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
