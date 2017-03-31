/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 12:03:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/31 03:43:05 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		clean_terminal(void)
{
	ft_putstr(tgetstr("cl", NULL));
	return (0);
}

void	set_pwd_env_var(t_shell **shell)
{
	char	*rdr;

	if ((rdr = (char*)malloc(sizeof(char) * BUFF_SIZE)))
	{
		do_setenv(shell, "PWD", getcwd(rdr, BUFF_SIZE));
		free(rdr);
	}
}

int		term_init(t_shell **shell)
{
	char	*term_name;
	char	*term_env;

	if (!(term_name = ttyname(0)))
		return (1);
	(!(get_env_val(shell, "PWD"))) ? set_pwd_env_var(shell) : (0);
	do_setenv(shell, "SHELL", get_env_val(shell, "PWD"));
	if (!(term_env = get_env_val(shell, "TERM")))
		do_setenv(shell, "TERM", "xterm-256color");
	if (tcgetattr(STDIN_FILENO, &(*shell)->term->term) == -1 ||
		tgetent(NULL, term_env) < 1)
		return (1);
	(*shell)->term->term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(*shell)->term->term) == -1)
		return (1);
	(*shell)->term->tc_ok = 1;
	return (0);
}

int		term_trigger(t_shell **shell, int off)
{
	if ((*shell)->term->tc_ok)
	{
		if (off)
			(*shell)->term->term.c_lflag |= (ICANON | ECHO);
		else
			(*shell)->term->term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN,
			&((*shell)->term->term)) == -1)
			return (1);
	}
	return (0);
}
