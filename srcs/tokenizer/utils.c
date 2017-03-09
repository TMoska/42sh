/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 03:34:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 03:41:53 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*tkn_new(char *data, int type)
{
	t_tkn	*node;

	if (!(node = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
		return (NULL);
	if (!data || !(node->data = ft_strdup(data)))
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
