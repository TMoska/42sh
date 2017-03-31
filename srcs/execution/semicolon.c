/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 23:21:50 by moska             #+#    #+#             */
/*   Updated: 2017/03/31 05:56:45 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_semicolon(t_tkn *node)
{
	int	left;
	int	right;

	left = execute_node(node->left);
	right = execute_node(node->right);
	return (!left && !right);
}
