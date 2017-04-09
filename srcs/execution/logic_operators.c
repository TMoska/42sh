/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:20:00 by moska             #+#    #+#             */
/*   Updated: 2017/04/09 12:43:32 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_logic_operators(t_tkn *node)
{
	int		ret;

	ret = execute_node(node->left);
	if ((ft_strcmp(node->data, "||") == 0 && ret != 0)
		|| (ft_strcmp(node->data, "&&") == 0 && ret == 0))
	{
		ret = execute_node(node->right);
	}
	return (ret);
}
