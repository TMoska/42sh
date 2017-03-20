/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:58:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/20 04:24:20 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perform_pipe(t_tkn *node, int fds[2], int stdin, int stdout)
{
	int		status;

	if (fork() == 0) {	// Child
		close(1);       /* close normal stdout */
		dup(fds[1]);   /* make stdout same as fds[1] */
		close(fds[0]); /* we don't need this */
		execute_node(node->left);
		dup2(stdout, 1);
		close(stdout);
		exit(0);
	} else {		// Parent
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WIFEXITED(status);
		close(0);       /* close normal stdin */
		dup(fds[0]);   /* make stdin same as fds[0] */
		close(fds[1]); /* we don't need this */
		if (*(node->right->data) == '|')
		{
			execute_node(node->right);
			interpret_line(node->right->left->data);
		}
		else if (node->right->type == 1 || node->right->type == 2)
			execute_node(node->right);
		else
			interpret_line(node->right->data);
		dup2(stdin, 0);
		close(stdin);
	}
}

int		execute_pipe(t_tkn *node)
{
	int		fds[2];
	int		stdin;
	int		stdout;

	pipe(fds);
	stdin = dup(0);
	stdout = dup(1);
	perform_pipe(node, fds, stdin, stdout);
	return (0);
}
