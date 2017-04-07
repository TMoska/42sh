/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:14:32 by moska             #+#    #+#             */
/*   Updated: 2017/04/06 02:16:35 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_right(t_tkn *node, int fd)
{
	int		stdout;
	int		ret;

	stdout = dup(1);
	dup2(fd, 1);
	ret = execute_node(node->left);
	dup2(stdout, 1);
	close(stdout);
	return (ret);
}

int		execute_right_redirection(t_tkn *node)
{
	t_tkn	*right_most;
	char	*f;
	int		fd;
	int		ops;

	right_most = node->right;
	ops = O_WRONLY | O_CREAT;
	ops |= ft_strcmp(node->data, ">") == 0 ? O_TRUNC : O_APPEND;
	while (right_most)
	{
		if (right_most->type == 1)
		{
			ops = O_WRONLY | O_CREAT;
			ops |= ft_strcmp(right_most->data, ">") == 0 ? O_TRUNC : O_APPEND;
		}
		f = (right_most->left) ? right_most->left->data : right_most->data;
		if ((fd = open(f, ops, 0644)) == -1)
			return (-1);
		(right_most->left && right_most->right) ? close(fd) : (0);
		right_most = right_most->right;
	}
	return (execute_right(node, fd));
}
