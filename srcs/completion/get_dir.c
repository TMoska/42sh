/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 06:59:20 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/06 07:12:20 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_dir(t_shell **shell)
{
	char *tmp;

	tmp = search_cmd(*shell);
	if (check_dir(tmp))
	{
		if (tmp[ft_strlen(tmp) - 1] != '/')
		{
			ft_strdel(&tmp);
			MOVE_UP;
			MOVE_UP;
			ft_putstr(tgoto(tgetstr("ch", NULL), 0, (*shell)->term->prompt_len
						+ (*shell)->term->tc_in));
			work_buffer(shell, "/");
			return (1);
		}
		return (0);
	}
	return (0);
}
