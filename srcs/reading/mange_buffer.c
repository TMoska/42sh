/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mange_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:32:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 19:33:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_buffer(t_shell **shell, char *buffer)
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

void		work_buffer(t_shell **shell, char *buffer)
{
	write_buffer(shell, buffer);
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(buffer);
	ft_putstr(tgetstr("ei", NULL));
}