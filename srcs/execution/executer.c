/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:40:38 by moska             #+#    #+#             */
/*   Updated: 2017/03/12 18:00:24 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	0	-	binary
**	1	-	>, >>
**	2	-	<, <<
**	3	-	&>
**	4	-	|
**	5	-	&&, ||
**	6	-	;
*/

int		execute_node(t_tkn *node)
{
	int		ret;

	ret = 0;
	if (!node)
		ret = 0;
	else if (node->type == 0)
		ret = interpret_line(node->data);
	else if (node->type == 1)
		ret = execute_right_redirection(node);
	else if (node->type == 2)
	{
	}
	else if (node->type == 3)
	{
	}
	else if (node->type == 4)
	{
	}
	else if (node->type == 5)
		ret = execute_logic_operators(node);
	else if (node->type == 6)
		ret = execute_semicolon(node);
	return (ret);
}
