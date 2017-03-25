/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 21:39:49 by moska             #+#    #+#             */
/*   Updated: 2017/03/25 21:41:11 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void	sig_callback(int s_num)
{
	t_shell *shell;

	shell = get_shell(NULL);
	if (s_num == SIGQUIT)
		exit(g_exit_code);
	else if (s_num == SIGINT)
		clean_buffer(&shell);
}

void	catch_signals(void)
{
	int i;

	i = 32;
	while (i > 0)
	{
		signal(i, sig_callback);
		i--;
	}
}

int		run_shell(t_shell **shell)
{
	while ((*shell)->exit != 1)
	{
		print_prompt(shell, NULL);
		catch_signals();
		if ((*shell)->tc_ok)
			read_input(shell, NULL);
		else
		{
			if (get_next_line(0, &(*shell)->buff) == 0)
				return (0);
		}
		do_quotes(shell);
		if (!validate_and_prep_cmd(shell))
		{
			ft_strdel(&((*shell)->buff));
			continue ;
		}
		hist_add(shell);
		(tokenize(shell) == 1) ? syn_error() : execute_node((*shell)->tree);
		mid_clean_shell(shell);
	}
	return ((*shell)->ret);
}

int		main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	g_exit_code = 0;
	shell = get_shell(env);
	term_init(&shell);
	clean_terminal();
	run_shell(&shell);
	clean_shell(&shell);
	return (shell->ret);
}
