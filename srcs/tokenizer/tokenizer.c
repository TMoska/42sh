/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/22 19:22:36 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_tokens(t_shell **shell)
{
	t_tkn	*tkns;
	int		i;

	i = 0;
	tkns = (*shell)->tkns;
	printf("Token count: %-5i\n\n", (*shell)->token_count);
	while (tkns)
	{
		printf("%i: %-10s type: %i\n", i + 1, tkns->data, tkns->type);
		tkns = tkns->right;
		i++;
	}
}

int			tokenize(t_shell **shell)
{
	if (get_tokens(shell) == 1)
		return (1);
	reorganize_tokens(shell);
	(*shell)->tree = build_tree((*shell)->tkns);
	(*shell)->tkns = NULL;
	return (0);
}
