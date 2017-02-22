/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 21:39:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/22 21:04:59 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void	sig_callback(int s_num)
{
	if (s_num == SIGINT || s_num == SIGQUIT)
		exit(g_exit_code);
}

int		run_shell(t_shell **shell)
{
	while (1)
	{
		print_prompt(shell);
		signal(SIGINT, sig_callback);
		signal(SIGQUIT, sig_callback);
		if (get_next_line(0, &((*shell)->buff)) == 0)
			exit(g_exit_code);
		if (!validate_and_prep_cmd(shell))
		{
			ft_strdel(&((*shell)->buff));
			continue ;
		}
		construct_command(shell);
		interpret_line(shell);
		mid_clean_shell(shell);
		if ((*shell)->exit == 1)
			return ((*shell)->ret);
	}
}

int		main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	g_exit_code = 0;
	create_shell(&shell, env);
	run_shell(&shell);
	clean_shell(&shell);
	return (shell->ret);
}
