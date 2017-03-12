/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:14:32 by moska             #+#    #+#             */
/*   Updated: 2017/03/12 22:30:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_right(t_tkn *node, int fd, int stdout)
{
	close(1);
	dup(fd);
	execute_node(node->left);
	dup2(stdout, 1);
	close(stdout);
}

int		execute_right_redirection(t_tkn *node)
{
	t_tkn	*right_most;
	char	*f;
	int		stdout;
	int		fd;
	int		ops;

	stdout = dup(1);
	right_most = node->right;
	while (right_most)
	{
		f = (right_most->left) ? right_most->left->data : right_most->data;
		ops = O_WRONLY | O_CREAT;
		ops |= ft_strcmp(node->data, ">") == 0 ? O_TRUNC : O_APPEND;
		fd = open(f, ops, 0644);
		(right_most->left && right_most->right) ? close(fd) : (0);
		right_most = right_most->right;
	}
	execute_right(node, fd, stdout);
	return (0);
}
