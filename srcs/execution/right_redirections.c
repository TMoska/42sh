/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:14:32 by moska             #+#    #+#             */
/*   Updated: 2017/03/11 23:21:21 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_right_redirection(t_tkn *node)
{
	int		stdout;
	int		fd;
	char	*f;
	t_tkn	*right_most;
	int		ops;

	stdout = dup(1);
	right_most = node->right;
	while (right_most)
	{
		f = (right_most->left) ? right_most->left->data : right_most->data;
		ops = O_WRONLY | O_CREAT;
		ops |= ft_strcmp(node->data, ">") == 0 ? O_TRUNC : O_APPEND;
		fd = open(f, ops, 0644);
		(right_most->left && right_most->right) ? close (fd) : (0);
		right_most = right_most->right;
	}
	close(1);
	dup(fd);
	execute_node(node->left);
	dup2(stdout, 1);
	close(stdout);
	return (0);
}
