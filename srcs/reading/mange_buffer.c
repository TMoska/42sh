/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mange_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:32:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/28 11:24:26 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_buffer(t_shell **shell, char *buffer)
{
	char	*ret;
	char	*ret1;
	int		in;
	int		len;
	char	*b;

	(*shell)->tc_len += 1;
	(*shell)->tc_in += 1;
	in = (*shell)->tc_in;
	len = (*shell)->tc_len;
	b = (*shell)->buff;
	if (!b && ((*shell)->buff = ft_strdup(buffer)))
		return ;
	ret = ((in > 1) ? ft_strndup(b, in - 1) : NULL);
	ret1 = (((len - in) > 0) ? ft_strdup(&b[in - 1]) : NULL);
	(*shell)->buff = ft_str3join(ret, buffer, ret1);
	ft_strdel(&ret);
	ft_strdel(&ret1);
	ft_strdel(&b);
}

void		work_buffer(t_shell **shell, char *buffer)
{
	write_buffer(shell, buffer);
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(buffer);
	ft_putstr(tgetstr("ei", NULL));
}
