/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganizer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 23:43:13 by moska             #+#    #+#             */
/*   Updated: 2017/03/20 21:25:26 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		move_node_back(t_tkn **start, t_tkn *ptr1)
{
	t_tkn *tmp;
	t_tkn *tmp2;
	t_tkn *tmp3;

	tmp = *start;
	tmp2 = *start;
	while (tmp->right != ptr1)
		tmp = tmp->right;
	while (tmp2->right->type <= ptr1->type && tmp2->right->type > 0)
		tmp2 = tmp2->right->right;
	tmp->right = tmp->right->right->right;
	tmp3 = tmp2->right;
	tmp2->right = ptr1;
	tmp2->right->right->right = tmp3;
}

static void		higher_type_node(t_tkn *start, t_tkn **ptr1,\
	int lower_than, int *post_pipe)
{
	*ptr1 = start->right;
	while (*ptr1 && (*ptr1)->right && in_range((*ptr1)->type, 1, 3) \
	&& (*ptr1)->type < lower_than)
		*ptr1 = (*ptr1)->right->right;
	*post_pipe = (*ptr1 && (*ptr1)->type == 4);
}

static void		search_for_new_separator(t_tkn **start, t_tkn **ptr1)
{
	while (*start && !in_range((*start)->type, 5, 6))
		*start = (*start)->right;
	if (*start && (*start)->right)
		move_pointers((*start)->right, start, ptr1, NULL);
	else
		*start = NULL;
}

static void		search_for_next_ptr_position(t_tkn *start, t_tkn **ptr1, \
	int *m_type, int *post_pipe)
{
	if (*ptr1 && (*ptr1)->right && (*ptr1)->right->right)
		*ptr1 = (*ptr1)->right->right;
	else
	{
		*ptr1 = NULL;
		while (!(*ptr1) && *m_type < 3)
		{
			(*m_type)++;
			higher_type_node(start, ptr1, *m_type, post_pipe);
		}
	}
	*post_pipe = (*ptr1 && (*ptr1)->type == 4);
}

void			arrange_nodes_in_priority(t_shell **shell)
{
	t_tkn	*start;
	t_tkn	*ptr1;
	t_tkn	*tmp;
	int		m_type;
	int		post_pipe;

	start = (*shell)->tkns;
	tmp = start;
	post_pipe = 0;
	higher_type_node(start, &ptr1, 2, &post_pipe);
	while (start)
	{
		m_type = 2;
		while (m_type <= 3 && ptr1 && in_range(ptr1->type, 1, 3) && !post_pipe)
		{
			if (ptr1->type < m_type && ptr1->type > 0)
			{
				move_node_back(&start, ptr1);
				higher_type_node(start, &ptr1, m_type, &post_pipe);
			}
			search_for_next_ptr_position(start, &ptr1, &m_type, &post_pipe);
		}
		search_for_new_separator(&start, &ptr1);
	}
	(*shell)->tkns = tmp;
}
