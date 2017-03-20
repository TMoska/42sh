/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 20:49:15 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/20 21:20:46 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perform_redirections(t_tkn *node, char *p1, char *p2)
{
	int	i1;
	int	i2;
	int	tmp_i1;

	if (!(i1 = ft_atoi(p1)))
		return ;
	if (*p2 == '-')
	{
		tmp_i1 = dup(i1);
		close(i1);
		execute_node(node->left);
		dup2(tmp_i1, i1);
	}
	else
	{
		if (!(i2 = ft_atoi(p2)))
			return ;
		tmp_i1 = dup(i1);
		close(i1);
		dup(i2);
		execute_node(node->left);
		dup2(tmp_i1, i1);
		close(tmp_i1);
	}
}

int		execute_fd_aggregation(t_tkn *node)
{
	char	*p1;
	char	*p2;
	char	*op;
	size_t	size;

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
	perform_redirections(node, p1, p2);
	ft_strdel(&p1);
	ft_strdel(&p2);
	return (0);
}
