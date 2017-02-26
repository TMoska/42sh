/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 19:37:58 by moska             #+#    #+#             */
/*   Updated: 2017/02/26 08:59:33 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identify_key(t_shell **shell, char *buffer, unsigned int key)
{
	(void)shell;
	(void)buffer;
	printf("%i\n", key);
	return (1);
}

void		read_input(t_shell **shell)
{
	char  *buffer;

	buffer = ft_strnew(5);
	while ((read(0, buffer, 5)) > 0 &&
		identify_key(shell, (char *)buffer, (unsigned int)*buffer))
	{
		ft_strdel(&buffer);
		buffer = ft_strnew(5);
	}
  // if (get_next_line(0, &((*shell)->buff)) == 0)
  //   exit(g_exit_code);
}