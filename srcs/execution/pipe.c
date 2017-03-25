/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:58:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 06:23:23 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_tkn *node, int fds[2], int stdout)
{
	close(1);
	dup(fds[1]);
	close(fds[0]);
	execute_node(node->left);
	dup2(stdout, 1);
	close(stdout);
	exit(0);
}

void	exec_parent(t_tkn *node, int fds[2], int stdin)
{
	int		status;

	close(0);
	dup(fds[0]);
	close(fds[1]);
	if (*(node->right->data) == '|')
	{
		execute_node(node->right);
		interpret_line(node->right->left->data);
	}
	else if (node->right->type == 1 || node->right->type == 2)
		execute_node(node->right);
	else
		interpret_line(node->right->data);
	wait(&status);
	if (WIFEXITED(status))
		g_exit_code = WIFEXITED(status);
	dup2(stdin, 0);
	close(stdin);
}

void	perform_pipe(t_tkn *node, int fds[2], int stdin, int stdout)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
	{
		ft_putendl_fd("fork error", 2);
		return ;
	}
	if (pid == 0)
		exec_child(node, fds, stdout);
	else
		exec_parent(node, fds, stdin);
}

int		execute_pipe(t_tkn *node)
{
	int		fds[2];
	int		stdin;
	int		stdout;

	if (pipe(fds) == -1)
	{
		ft_putendl_fd("pipe error", 2);
		return (-1);
	}
	stdin = dup(0);
	stdout = dup(1);
	perform_pipe(node, fds, stdin, stdout);
	return (0);
}
