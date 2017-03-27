/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 11:05:54 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/27 23:07:27 by adeletan         ###   ########.fr       */
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
		(*shell)->history->at_index = -1;
		print_prompt(shell, NULL);
		catch_signals();
		if ((*shell)->term->tc_ok)
			read_input(shell, NULL);
		else
		{
			if (get_next_line(0, &(*shell)->buff) == 0)
				return (0);
		}
		if (validate_and_prep_cmd(shell) == -1)
		{
			ft_strdel(&((*shell)->buff));
			continue ;
		}
		hist_add(shell);
		do_quotes(shell);
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
