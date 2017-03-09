/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 22:24:05 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_shell **shell)
{
	t_tkn *tkns;

	tkns = (*shell)->tkns;
	while (tkns)
	{
		printf("s: `%s` type: %i\n", tkns->data, tkns->type);
		tkns = tkns->right;
	}
}

void		tokenize(t_shell **shell)
{
	get_tokens(shell);
	print_tokens(shell);
}
