/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:58:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/11 03:22:11 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_child(t_tkn *node, int fds[2], int stdout)
{
	dup2(fds[1], 1);
	close(fds[0]);
	execute_node(node->left);
	dup2(stdout, 1);
	close(stdout);
	exit(g_exit_code);
}

void		exec_parent(t_tkn *node, int fds[2], int stdin)
{
	dup2(fds[0], 0);
	close(fds[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	execute_node(node->right);
	dup2(stdin, 0);
	close(stdin);
	exit(g_exit_code);
}

int			fork_error(void)
{
	ft_putendl_fd("fork error", 2);
	return (1);
}

static int	perform_pipe(t_tkn *node, int fds[2], int stdin, int stdout)
{
	pid_t	pid_child_left;
	pid_t	pid_child_right;
	int		status1;
	int		status2;

	if ((pid_child_right = fork()) == -1 && fork_error())
		return (-1);
	else if (!pid_child_right)
		exec_parent(node, fds, stdin);
	if ((pid_child_left = fork()) == -1 && fork_error())
		return (-1);
	else if (!pid_child_left)
		exec_child(node, fds, stdout);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid_child_right, &status1, 0);
	waitpid(pid_child_left, &status2, 0);
	return (!(WIFEXITED(status1) && WEXITSTATUS(status1) == 0));
}

int			execute_pipe(t_tkn *node)
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
	return (perform_pipe(node, fds, stdin, stdout));
}
