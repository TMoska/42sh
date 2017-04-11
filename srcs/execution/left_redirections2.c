/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 17:26:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/11 17:31:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_heredoc(char *f)
{
	t_shell		*shell;
	t_list		*tmp;
	t_list		*hd_lst;

	shell = get_shell(NULL);
	tmp = shell->heredoc;
	hd_lst = last_matching_opening(&shell, f);
	hd_lst = hd_lst->next;
	while (((t_heredoc*)(hd_lst->content))->type != 2)
	{
		ft_putendl(((t_heredoc*)(hd_lst->content))->txt);
		hd_lst = hd_lst->next;
	}
}

static void		left_redir_child(int fds[2], int stdout, char *f)
{
	dup2(fds[1], 1);
	close(fds[0]);
	print_heredoc(f);
	dup2(stdout, 1);
	close(stdout);
	exit(g_exit_code);
}

static void		left_redir_parent(int fds[2], int stdin, t_tkn *node)
{
	int		status;

	dup2(fds[0], 0);
	close(fds[1]);
	wait(&status);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
	exit(g_exit_code);
}

static int		perform_two_left(t_tkn *node, int stdin, int stdout, char *f)
{
	int		fds[2];
	int		status;
	pid_t	pid_child_left;
	pid_t	pid_child_right;

	if (pipe(fds) == -1)
	{
		ft_putendl_fd("pipe error", 2);
		return (-1);
	}
	if ((pid_child_left = fork()) == -1 && fork_error())
		return (-1);
	else if (!pid_child_left)
		left_redir_parent(fds, stdin, node);
	if ((pid_child_right = fork()) == -1 && fork_error())
		return (-1);
	else if (!pid_child_right)
		left_redir_child(fds, stdout, f);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid_child_right, &status, 0);
	waitpid(pid_child_left, &status, 0);
	return (0);
}

int				execute_two_left(t_tkn *node, char *f)
{
	int		stdin;
	int		stdout;

	stdin = dup(0);
	stdout = dup(1);
	return (perform_two_left(node, stdin, stdout, f));
}
