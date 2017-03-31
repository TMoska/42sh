/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mange_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:32:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/31 04:29:16 by adeletan         ###   ########.fr       */
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

	len = ft_strlen(buffer);
	(*shell)->term->tc_len += len;
	(*shell)->term->tc_in += len;
	in = (*shell)->term->tc_in;
	len = (*shell)->term->tc_len;
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

int			reset_line(t_shell **shell)
{
	(*shell)->term->tc_in = 0;
	(*shell)->term->tc_len = 0;
	return (0);
}

void		work_buffer(t_shell **shell, char *buffer)
{

	int i;

	i = ft_strlen(buffer);
	write_buffer(shell, buffer);
	(*shell)->term->tc_in -= i;
	while (i--)
		move_right(shell, NULL, 1);
	ft_printbuffer(shell);
}
