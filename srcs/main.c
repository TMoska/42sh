/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 11:05:54 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/11 13:53:30 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void	sig_resize(int s_num)
{
	t_c_tab		*list;
	t_shell		*shell;
	size_t		number;

	signal(SIGWINCH, SIG_IGN);
	number = 0;
	(void)s_num;
	if ((list = get_list(NULL, 0)))
	{
		shell = get_shell(NULL);
		ft_putstr(tgetstr("cl", NULL));
		print_prompt(&shell, NULL);
		ft_putstr(shell->buff);
		if (!big_enough(list))
		{
			ioctl(0, TIOCSTI, "n");
			clean_list(list);
			get_list(NULL, 1);
			return ;
		}
		begin_resize_tab(&list, number);
	}
	signal(SIGWINCH, sig_resize);
	return ;
}

void	sig_callback(int s_num)
{
	t_shell *shell;
	t_c_tab	*list;

	shell = get_shell(NULL);
	list = get_list(NULL, 0);
	if (s_num == SIGQUIT)
		exit(g_exit_code);
	else if (s_num == SIGINT)
	{
		DEL_LINES;
		if (list)
		{
			tab_term(2, shell, 1);
			clean_list(list);
			get_list(NULL, 1);
			ioctl(0, TIOCSTI, "n");
		}
		clean_buffer(&shell);
	}
}

void	catch_signals(void)
{
	int i;

	i = 32;
	while (i > 0)
		signal(i--, sig_callback);
	signal(SIGWINCH, sig_resize);
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
		do_quotes(shell);
		if (validate_and_prep_cmd(shell) == -1)
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
	if (term_init(&shell))
	{
		ft_putendl_fd("Error: shell could not be initialized", 2);
		return (1);
	}
	clean_terminal();
	run_shell(&shell);
	clean_shell(&shell);
	return (shell->ret);
}
