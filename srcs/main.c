/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 21:39:49 by moska             #+#    #+#             */
/*   Updated: 2017/02/17 19:20:05 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
◦ malloc, free
◦ access
◦ open, close, read, write
◦ opendir, readdir, closedir
◦ getcwd, chdir
◦ stat, lstat, fstat
◦ fork, execve
◦ wait, waitpid, wait3, wait4
◦ signal, kill
◦ exit
*/

#include "minishell.h"

// static void print_shell(t_shell **shell)
// {
// 	printf("SHELL\n");
// 	printf("=====\n");
// 	printf("->buff %s\n", (*shell)->buff);
// 	if ((*shell)->cmd)
// 		printf("->cmd[0] %s\n", (*shell)->cmd[0]);
// 	printf("->cmd_len %i\n", (*shell)->cmd_len);
// 	printf("->ret %i\n", (*shell)->ret);
// 	printf("->exit %i\n", (*shell)->exit);
// }

void	sig_callback(int s_num)
{
	if (s_num == SIGINT) // Todo: Support more terimnation signals
	{
		print_prompt(1);
		printf("%s\n", "TERMINATIING");
		exit(0);
	}
}

int		run_shell(t_shell **shell)
{
	while (1)
	{
		// print_shell(shell);
		print_prompt(0);
		signal(SIGINT, sig_callback);
		get_next_line(0, &((*shell)->buff));
		if (!validate_and_prep_cmd(shell))
		{
			ft_strdel(&((*shell)->buff));
			continue ;
		}
		construct_command(shell);
		interpret_line(shell);
		mid_clean_shell(shell);
		if ((*shell)->exit == 1)
		{
			printf("EXIT\n");
			return (0);
		}
	}
}

int main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	create_shell(&shell, env);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
