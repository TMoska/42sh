/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:40:38 by moska             #+#    #+#             */
/*   Updated: 2017/03/11 17:54:32 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_node(t_tkn *node)
{
	int		ret;

	ret = 0;
	if (!node)
		ret = 0;
	else if (node->type == 0) // binary
		ret = interpret_line(node->data);
	else if (node->type == 1) // >, >>
	{

	}
	else if (node->type == 2) // <, <<
	{

	}
	else if (node->type == 3) // &>
	{

	}
	else if (node->type == 4) // |
	{

	}
	else if (node->type == 5) // && or ||
	{
		ret  = execute_node(node->left);
		if ((ft_strcmp(node->data, "||") == 0 && ret != 0)
			|| (ft_strcmp(node->data, "&&") == 0 && ret == 0))
			ret = execute_node(node->right);
	}
	else if (node->type == 6) // semicolon (;)
	{
		execute_node(node->left);
		execute_node(node->right);
	}
	return (ret);
}

void	execute_tree(t_shell **shell)
{
	execute_node((*shell)->tree);
}
