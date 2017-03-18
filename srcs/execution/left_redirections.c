/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 20:58:35 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/18 16:51:24 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirection_type(t_tkn *node)
{
	return (ft_strcmp(node->data, "<<") == 0 ? 2 : 1);
}

void	execute_left(t_tkn *node, int fd)
{
	int		stdin;

	stdin = dup(0);
	close(0);
	dup(fd);
	execute_node(node->left);
	dup2(stdin, 0);
	close(stdin);
}

void	read_heredoc(int fd, char **f)
{
	t_shell *shell;
	char	*buff_tmp;

	fd = open(".21sh_heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	shell = get_shell(NULL);
	buff_tmp = ft_strdup(shell->buff);
	while (1)
	{
		print_prompt(&shell, ft_strdup(">"));
		read_input(&shell);
		if (ft_strcmp(shell->buff, *f) == 0)
			break ;
		write(fd, shell->buff, ft_strlen(shell->buff));
		write(fd, "\n", 1);
	}
	close(fd);
	*f = ".21sh_heredoc_tmp";
	ft_strdel(&shell->buff);
	shell->buff = buff_tmp;
}

int		check_errors(char *f_name)
{
	t_shell *shell;

	shell = get_shell(NULL);
	if (access(f_name, F_OK) != -1)
	{
		if (access(f_name, R_OK) == -1)
			permission_denied(&shell, FALSE, f_name);
	}
	else
		no_file_or_dir(&shell, FALSE);
	shell->cmd = ft_strsplit("", ' ');
	return (-1);
}

int		execute_left_redirection(t_tkn *node)
{
	t_tkn	*right_most;
	char	*f;
	int		fd;
	int		type;

	type = redirection_type(node);
	right_most = node->right;
	while (right_most)
	{
		f = (right_most->left) ? right_most->left->data : right_most->data;
		if (type == 2)
			read_heredoc(fd, &f);
		if ((fd = open(f, O_RDONLY)) == -1)
			return (check_errors(f));
		(right_most->left && right_most->right) ? close(fd) : (0);
		type = redirection_type(node);
		right_most = right_most->right;
	}
	execute_left(node, fd);
	return (0);
}
