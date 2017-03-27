/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:58:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/27 20:11:26 by tmoska           ###   ########.fr       */
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
	close(0);
	dup(fds[0]);
	close(fds[1]);
	execute_node(node->right);
	dup2(stdin, 0);
	close(stdin);
	exit(0);
}

int		fork_error(void)
{
	ft_putendl_fd("fork error", 2);
	return (1);
}

void	perform_pipe(t_tkn *node, int fds[2], int stdin, int stdout)
{
	pid_t	pid_child_left;
	pid_t	pid_child_right;
	int		status;

	if ((pid_child_right = fork()) == -1 && fork_error())
		return ;
	else if (!pid_child_right)
		exec_parent(node, fds, stdin);
	if ((pid_child_left = fork()) == -1 && fork_error())
		return ;
	else if (!pid_child_left)
		exec_child(node, fds, stdout);
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
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
