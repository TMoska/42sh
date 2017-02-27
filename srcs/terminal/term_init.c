/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 12:03:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/26 17:58:36 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		term_init(t_shell **shell)
{
	if (!isatty(0))
		exit(1);
	// if (tcgetattr(STDIN_FILENO, &term) == -1 ||
	// 	tgetent(NULL, get_env_val(shell, "TERM")) < 1)
	if (tcgetattr(STDIN_FILENO, &((*shell)->term)) == -1)
		return (1);
	(*shell)->term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(*shell)->term);
	return (0);
}