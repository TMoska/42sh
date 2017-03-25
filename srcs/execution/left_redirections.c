/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 20:58:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 07:08:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_single_left(t_tkn *node, int fd)
{
	int		stdin;

	stdin = dup(0);
	close(0);
	dup(fd);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
}

static void	execute_two_left(t_shell **shell, t_tkn *node)
{
	t_list	*lst;
	// int		tmp_i1;
	int		fds[2];
	int		stdin;
	int		stdout;

	lst = (*shell)->heredoc;
	pipe(fds);
	stdin = dup(0);
	stdout = dup(1);


	close(0);
	dup(fds[0]);
	close(fds[1]);
	execute_node(node->left);

	close(1);
	dup(fds[1]);
	close(fds[0]);
	while (lst)
	{
		ft_putendl_fd((char*)lst->content, fds[0]);
		lst = lst->next;
	}

	dup2(stdout, 1);
	close(stdout);

	dup2(stdin, 0);
	close(stdin);

	//
	// tmp_i1 = dup(1);
	// close(1);
	// dup(0);
	// while (lst)
	// {
	// 	ft_putendl_fd((char*)lst->content, 1);
	// 	lst = lst->next;
	// }
	// execute_node(node->left);
	// dup2(tmp_i1, 1);
	// close(tmp_i1);
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

static void	find_heredoc(t_shell **shell, char **f)
{
	(void)shell;
	(void)f;
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
		(type == 2) ? find_heredoc(&shell, &f) : (0);
		if ((type == 1) && (fd = open(f, O_RDONLY)) == -1)
			return (check_errors(f, &shell));
		(right_most->left && right_most->right) ? close(fd) : (0);
		type = redirection_type(node);
		right_most = right_most->right;
	}
	// ft_print_list(shell->heredoc);
	(type == 1) ? execute_single_left(node, fd) : execute_two_left(&shell, node);
	return (0);
}
