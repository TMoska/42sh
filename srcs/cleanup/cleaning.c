/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:11:46 by moska             #+#    #+#             */
/*   Updated: 2017/04/11 17:29:46 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_btree(t_tkn *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		clean_btree(tree->left);
	if (tree->right)
		clean_btree(tree->right);
	ft_strdel(&tree->data);
	free(tree);
}

void	del_lst_str(void **content, size_t *content_size)
{
	(void)content_size;
	ft_strdel((char**)content);
}

void	mid_clean_shell(t_shell **shell)
{
	ft_lstdel(&(*shell)->commands, del_lst_str);
	ft_strdel(&((*shell)->buff));
	clean_btree((*shell)->tree);
	ft_lstdel(&(*shell)->heredoc, del_heredoc);
}

void	clean_history(t_h_lst **lst)
{
	t_h_lst	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_strdel(&tmp->cmd);
		free(tmp);
	}
}

void	clean_shell(t_shell **shell)
{
	ft_str2del(&(*shell)->env);
	clean_env_list(&(*shell)->env_list);
	clean_history(&(*shell)->history->list);
	ft_memdel((void **)(&(*shell)->history));
	ft_memdel((void **)&(*shell)->term);
	free((*shell)->q);
	free(*shell);
}
