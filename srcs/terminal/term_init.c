/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 12:03:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/27 20:11:49 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		term_init(t_shell **shell)
{
	char	*term_name;

	term_name = ttyname(0);
	if (term_name == NULL)
		return (1);
	if (tcgetattr(STDIN_FILENO, &(*shell)->term) == -1 ||
		tgetent(NULL, get_env_val(shell, "TERM")) < 1)
		return (1);
	(*shell)->term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(*shell)->term) == -1)
		return (1);
	(*shell)->tc_ok = 1;
	return (0);
}

int		term_trigger(t_shell **shell, int off)
{
	if ((*shell)->tc_ok)
	{
		if (off)
			(*shell)->term.c_lflag |= (ICANON | ECHO);
		else
			(*shell)->term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &((*shell)->term)) == -1)
			return (1);
	}
	return (0);
}
