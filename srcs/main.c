/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 21:39:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/19 17:52:22 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_callback(int s_num)
{
	if (s_num == SIGINT) // Todo: Support more terimnation signals
	{
		// print_prompt(NULL, 1);
		exit(0);
	}
}

int		run_shell(t_shell **shell)
{
	while (1)
	{
		print_prompt(shell, 0);
		signal(SIGINT, sig_callback);
		if (get_next_line(0, &((*shell)->buff)) == 0)
			exit(0);
		if (!validate_and_prep_cmd(shell))
		{
			ft_strdel(&((*shell)->buff));
			continue ;
		}
		construct_command(shell);
		interpret_line(shell);
		mid_clean_shell(shell);
		if ((*shell)->exit == 1)
			return (0);
	}
}

int		main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	create_shell(&shell, env);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
