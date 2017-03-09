/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 03:34:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 23:13:17 by moska            ###   ########.fr       */
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
		t_tkn	*pre_src;
		t_tkn	*tmp_src;

		tmp = (*dst)->data;
		pre_src = *dst;
		tmp_src = *src;
		(*dst)->data = ft_str3join(tmp, " ", (*src)->data);
		while (pre_src->right != *src)
			pre_src = pre_src->right;
		pre_src->right = (*src)->right;
		ft_strdel(&tmp);
		ft_strdel(&tmp_src->data);
		free(tmp_src);
}
