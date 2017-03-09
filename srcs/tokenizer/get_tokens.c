/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 12:10:11 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_a_priority_type(char *s, int *type)
{
	if ((ft_strcmp(s, ";") == 0))
		(*type) = 6;
	else if (ft_strcmp(s, "||") == 0 || ft_strcmp(s, "&&") == 0)
		(*type) = 5;
	else if (ft_strcmp(s, "|") == 0)
		(*type) = 4;
	else if (ft_strstr(s, "&>"))
		(*type) = 3;
	else if (ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0)
		(*type) = 2;
	else if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0)
		(*type) = 1;
	else
		(*type) = 0;
}

void		get_tokens(t_shell **shell)
{
	t_tkn	*tkns;
	t_tkn	*token;
	t_tkn	*token1;
	char	**cmds;
	int		i;
	int		type;

	tkns = NULL;
	i = 0;
	cmds = split_command((*shell)->buff);
	while (cmds[i])
	{
		assign_a_priority_type(cmds[i], &type);
		tkn_new_to_back(&tkns, cmds[i], type);
		printf("s: `%s` type: %i\n", cmds[i], type);
		i++;
	}
	token = tkns;
	token1 = tkns->right->right->right;
	printf("=====\n");
	ft_str2del(&cmds);
	printf("Merging: %s and %s\n", token->data, token1->data);
	tkn_merge_nodes(&token, &token1);
	while (tkns)
	{
		printf("s: `%s` type: %i\n", tkns->data, tkns->type);
		tkns = tkns->right;
	}
	(*shell)->tkns = tkns;
}