/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 20:58:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/23 23:34:21 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_left(t_tkn *node, int fd)
{
	int		stdin;

	stdin = dup(0);
	close(0);
	dup(fd);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
}

static void	read_heredoc(int fd, char **f, t_shell **shell)
{
	char	*buff_tmp;

	fd = open(".21sh_heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	buff_tmp = ft_strdup((*shell)->buff);
	while (1)
	{
		print_prompt(shell, ft_strdup(">"));
		read_input(shell, *f);
		if (ft_strcmp((*shell)->buff, *f) == 0)
			break ;
		write(fd, (*shell)->buff, ft_strlen((*shell)->buff));
		write(fd, "\n", 1);
	}
	close(fd);
	*f = ".21sh_heredoc_tmp";
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = buff_tmp;
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

int			execute_left_redirection(t_tkn *node, int pre_condition)
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
		if (!pre_condition && shell->pipe_and_redir && !open_tmp_heredoc(&fd))
			break ;
		f = (right_most->left) ? right_most->left->data : right_most->data;
		(type == 2) ? read_heredoc(fd, &f, &shell) : (0);
		if ((fd = open(f, O_RDONLY)) == -1)
			return (check_errors(f, &shell));
		(right_most->left && right_most->right) ? close(fd) : (0);
		type = redirection_type(node);
		right_most = right_most->right;
	}
	(!pre_condition) ? execute_left(node, fd) : (0);
	return (0);
}
