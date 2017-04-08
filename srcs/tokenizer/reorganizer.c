/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 23:32:59 by moska             #+#    #+#             */
/*   Updated: 2017/04/09 01:43:04 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			in_range(int i, int start, int end)
{
	return ((i <= end && i >= start));
}

void		move_pointers(t_tkn *init, t_tkn **start, \
	t_tkn **ptr1, t_tkn **ptr2)
{
	if (!init)
		return ;
	*start = init;
	*ptr1 = (*start)->right;
	if (ptr2)
		*ptr2 = (*ptr1) ? (*ptr1)->right : NULL;
}

static void	move_args_around(t_shell **shell)
{
	t_tkn	*start;
	t_tkn	*ptr1;
	t_tkn	*ptr2;

	move_pointers((*shell)->tkns, &start, &ptr1, &ptr2);
	while (start && ptr2)
	{
		while (ptr2 && !in_range(ptr1->type, 4, 6))
		{
			if ((ptr2 && in_range(ptr1->type, 1, 3)
				&& ft_word_count(ptr2->data, ' ') >= 2) ||
				(ptr1->type == 3 && ptr2->type == 0))
			{
				tkn_move_args_to_start(&start, &ptr2);
				move_args_around(shell);
				return ;
			}
			ptr1 = ptr1->right;
			ptr2 = ptr2->right;
		}
		if (in_range(ptr1->type, 4, 6))
			move_pointers(ptr1->right, &start, &ptr1, &ptr2);
	}
}

void		reorganize_tokens(t_shell **shell)
{
	move_args_around(shell);
	arrange_nodes_in_priority(shell);
}
