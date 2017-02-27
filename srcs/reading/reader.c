/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 19:37:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/26 20:26:11 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		write_to_buffer(t_shell **shell, char *buffer)
{
	char	*tmp;

	if (!(*shell)->buff && ((*shell)->buff = ft_strdup(buffer)))
		return ;
	tmp = (*shell)->buff;
	(*shell)->buff = ft_strjoin((*shell)->buff, buffer);
	ft_strdel(&tmp);
}

void	work_on_buffer(t_shell **shell, char *buffer)
{
	write_to_buffer(shell, buffer);
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(buffer);
	ft_putstr(tgetstr("ei", NULL));
}

static int	identify_key(t_shell **shell, char *buffer, unsigned int key)
{
	(void)shell;
	(void)buffer;
	if (key != BTN_ENTER && ft_isprint(key))
		write_to_buffer(shell, buffer);
	if (key == BTN_ENTER)
		return (0);
	return (1);
}

void		read_input(t_shell **shell)
{
	char			*buffer[5];
	unsigned int 	btn_code;

	ft_memset(buffer, 0, 5);
	btn_code = 0;
	while ((read(0, buffer, 5)) > 0 &&
		identify_key(shell, (char *)buffer, (unsigned int)*buffer))
	{
		btn_code += (unsigned int)*buffer;
		ft_memset(buffer, 0, 5);
	}
	ft_putchar('\n');
}