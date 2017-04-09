/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 20:49:15 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/09 12:44:06 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		perform_redirections(t_tkn *node, char *p1, char *p2)
{
	int	i1;
	int	i2;
	int	tmp_i1;

	i1 = ft_atoi(p1);
	i2 = ft_atoi(p2);
	if ((!i1 && ft_strcmp(p1, "0") != 0) || !p2 || (*p2 != '-' && !i2))
	{
		syn_error();
		return (-1);
	}
	tmp_i1 = dup(i1);
	(*p2 != '-') ? dup2(i2, i1) : close(i1);
	execute_node(node->left);
	dup2(tmp_i1, i1);
	close(tmp_i1);
	return (0);
}

int		execute_fd_aggregation(t_tkn *node)
{
	char	*p1;
	char	*p2;
	char	*op;
	size_t	size;
	int		ret;

	size = 0;
	op = node->data;
	while (op[size] != '>')
		size++;
	if (!(p1 = ft_strndup(op, size)))
		p1 = ft_strdup("1");
	op += (2 + size);
	size = 0;
	while (op[size] != '\0')
		size++;
	p2 = ft_strndup(op, size);
	ret = perform_redirections(node, p1, p2);
	ft_strdel(&p1);
	ft_strdel(&p2);
	return (ret);
}
