/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/04/01 18:58:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tokenize(t_shell **shell)
{
	if (get_tokens(shell) == 1)
		return (1);
	reorganize_tokens(shell);
	scan_heredocs(shell);
	(*shell)->tree = build_tree((*shell)->tkns);
	(*shell)->tkns = NULL;
	return (0);
}
