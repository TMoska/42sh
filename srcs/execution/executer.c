/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:40:38 by moska             #+#    #+#             */
/*   Updated: 2017/03/11 23:24:03 by moska            ###   ########.fr       */
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
		ret = execute_right_redirection(node);
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
		ret = execute_logic_operators(node);
	else if (node->type == 6) // semicolon (;)
		ret = execute_semicolon(node);
	return (ret);
}

void	execute_tree(t_shell **shell)
{
	execute_node((*shell)->tree);
}
