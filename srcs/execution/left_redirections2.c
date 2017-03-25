/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 17:26:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/25 18:46:45 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_heredoc(char *f)
{
	t_shell		*shell;
	t_list		*tmp;

	shell = get_shell(NULL);
	tmp = shell->heredoc;
	while (ft_strcmp(shell->heredoc->content, f) != 0)
	{
		tmp = shell->heredoc;
		shell->heredoc = shell->heredoc->next;
		ft_lstdelone(&tmp, &del_lst_str);
	}
	shell->heredoc = shell->heredoc->next;
	ft_lstdelone(&tmp, &del_lst_str);
	while (ft_strcmp(shell->heredoc->content, f) != 0)
	{
		ft_putendl(shell->heredoc->content);
		tmp = shell->heredoc;
		shell->heredoc = shell->heredoc->next;
		ft_lstdelone(&tmp, &del_lst_str);
	}
	shell->heredoc = shell->heredoc->next;
	ft_lstdelone(&tmp, &del_lst_str);
}

static void		left_redir_child(int fds[2], char *f)
{
	int	stdout;

	stdout = dup(1);
	close(1);
	dup(fds[1]);
	close(fds[0]);
	print_heredoc(f);
	dup2(stdout, 1);
	close(stdout);
	exit(0);
}

static void		left_redir_parent(int fds[2], t_tkn *node)
{
	int		stdin;
	int		status;

	stdin = dup(0);
	close(0);
	dup(fds[0]);
	close(fds[1]);
	wait(&status);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
}

static int		pipe_and_fork(pid_t *pid, int fds[2])
{
	if (pipe(fds) == -1)
	{
		ft_putendl_fd("pipe error", 2);
		return (-1);
	}
	if ((*pid = fork()) == -1)
	{
		ft_putendl_fd("fork error", 2);
		return (-1);
	}
	return (0);
}

int				execute_two_left(t_tkn *node, char *f)
{
	int		fds[2];
	pid_t	pid;

	if ((pipe_and_fork(&pid, fds) == -1))
		return (-1);
	if (pid == 0)
		left_redir_child(fds, f);
	else
		left_redir_parent(fds, node);
	return (0);
}
