/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 20:58:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/01 00:28:35 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_single_left(t_tkn *node, int fd)
{
	int		stdin;

	stdin = dup(0);
	dup2(fd, 0);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
}

static int	check_errors(char *f_name, t_shell **shell)
{
	if (access(f_name, F_OK) != -1)
	{
		if (access(f_name, R_OK) == -1)
			permission_denied(shell, FALSE, f_name);
	}
	else
		no_file_or_dir(shell, FALSE);
	return (-1);
}

int			execute_left_redirection(t_tkn *node)
{
	t_tkn	*right_most;
	char	*f;
	int		fd;
	int		type;
	t_shell	*shell;

	shell = get_shell(NULL);
	type = redirection_type(node);
	right_most = node->right;
	while (right_most)
	{
		f = (right_most->left) ? right_most->left->data : right_most->data;
		if ((type == 1) && (fd = open(f, O_RDONLY)) == -1)
			return (check_errors(f, &shell));
		(right_most->left && right_most->right) ? close(fd) : (0);
		if (right_most->right)
			type = redirection_type(right_most);
		right_most = right_most->right;
	}
	if (type == 1)
		execute_single_left(node, fd);
	else if (execute_two_left(node, f) == -1)
		return (-1);
	return (0);
}
