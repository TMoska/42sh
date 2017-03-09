/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 03:34:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 12:13:33 by tmoska           ###   ########.fr       */
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

int		tkn_new_to_back(t_tkn **lst, char *data, int type)
{
	t_tkn *new;
	t_tkn *tmp;

	tmp = *lst;
	if (!(new = tkn_new(data, type)))
		return (0);
	if (tmp)
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new;
	}
	else
		*lst = new;
	return (1);
}

void	tkn_merge_nodes(t_tkn **dst, t_tkn **src)
{
		char	*tmp;
		t_tkn	*tmp_token;

		tmp = (*dst)->data;
		(*dst)->data = ft_str3join(tmp, " ", (*src)->data);
		tmp_token = (*src)->left;
		if ((*src)->left)
			(*src)->left->right = (*src)->right;
		if (tmp_token && (*src)->right)
			((*src)->right)->left = tmp_token;
		ft_strdel(&tmp);
		ft_strdel(&(*src)->data);
		// free(src);
}
