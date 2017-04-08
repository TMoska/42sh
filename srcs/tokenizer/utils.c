/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 03:34:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/09 01:27:38 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*tkn_pre_last(t_tkn *lst)
{
	t_tkn	*node;

	node = lst;
	while (node->right)
		node = node->right;
	return (node);
}

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

char	*ft_join_arr_to_str(char **arr)
{
	char	*tmp;
	char	**tmp_arr;
	char	*res;

	tmp_arr = arr;
	res = ft_strdup(*tmp_arr);
	tmp_arr++;
	while (*tmp_arr)
	{
		tmp = res;
		res = ft_str3join(res, " ", *tmp_arr);
		tmp_arr++;
		ft_strdel(&tmp);
	}
	return (res);
}

void	tkn_move_args_to_start(t_tkn **dst, t_tkn **src)
{
	char	*tmp;
	char	*tmp_dst;
	char	*tmp_src;
	char	**src_data_tab;

	tmp_dst = (*dst)->data;
	tmp_src = (*src)->data;
	src_data_tab = ft_strsplit((*src)->data, ' ');
	if (prev_node_not_fd_aggr(*dst, *src))
	{
		tmp = ft_join_arr_to_str(&(src_data_tab[1]));
		(*src)->data = ft_strdup(src_data_tab[0]);
		ft_strdel(&tmp_src);
	}
	else
	{
		tmp = ft_join_arr_to_str(&(src_data_tab[0]));
		tkn_del(*dst, src);
	}
	(*dst)->data = ft_str3join(tmp_dst, " ", tmp);
	ft_strdel(&tmp_dst);
	ft_strdel(&tmp);
	ft_str2del(&src_data_tab);
}
