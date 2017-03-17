/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:58:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/16 15:49:51 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_pipe(t_tkn *node)
{
	int fds[2];
	int	stdin;
	int	stdout;
	pid_t pid;

	pipe(fds);
	stdin = dup(0);
	stdout = dup(1);
	pid = fork();
	if (pid == 0) {
		close(1);       /* close normal stdout */
		dup(fds[1]);   /* make stdout same as fds[1] */
		close(fds[0]); /* we don't need this */
		execute_node(node->left);
		dup2(stdout, 1);
		close(stdout);
	} else {
		close(0);       /* close normal stdin */
		dup(fds[0]);   /* make stdin same as fds[0] */
		close(fds[1]); /* we don't need this */
		interpret_line(node->right->data);
		dup2(stdin, 0);
		close(stdin);
	}
	return (0);
}
