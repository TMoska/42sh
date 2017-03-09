/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 23:13:47 by moska            ###   ########.fr       */
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
		i++;
	}
	ft_str2del(&cmds);
	(*shell)->tkns = tkns;
}
