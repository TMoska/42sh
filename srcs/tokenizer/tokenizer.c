/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/12 00:04:32 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_shell **shell)
{
	t_tkn	*tkns;
	int 	i = 0;

	tkns = (*shell)->tkns;
	printf("Token count: %-5i\n\n", (*shell)->token_count);
	while (tkns)
	{
		printf("%i: %-10s type: %i\n", i + 1, tkns->data, tkns->type);
		tkns = tkns->right;
		i++;
	}
}

void		tokenize(t_shell **shell)
{
	get_tokens(shell);
	reorganize_tokens(shell);
	(*shell)->tree = build_tree((*shell)->tkns);
	(*shell)->tkns = NULL;
}
