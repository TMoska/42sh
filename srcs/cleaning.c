/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:11:46 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 10:56:42 by tmoska           ###   ########.fr       */
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

void	clean_list(void **a, size_t *b)
{
	(void)b;
	ft_strdel((char**)a);
}

void	mid_clean_shell(t_shell **shell)
{
	(void)shell;
	ft_lstdel(&(*shell)->commands, clean_list);
	ft_strdel(&((*shell)->buff));
	clean_btree((*shell)->tkns);
}

void	clean_shell(t_shell **shell)
{
	ft_str2del(&(*shell)->env);
	clean_env_list(&(*shell)->env_list);
	free((*shell)->q);
}
