/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/22 18:39:25 by tmoska           ###   ########.fr       */
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
	else if (ft_strstr(s, ">&"))
		(*type) = 3;
	else if (ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0)
		(*type) = 2;
	else if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0)
		(*type) = 1;
	else
		(*type) = 0;
}

int			error_check(t_tkn *tkns)
{
	t_tkn	*nd;
	int		i;

	i = 0;
	nd = tkns;
	// nd = tkn_pre_last(tkns);
	while (nd)
	{
		if (i == 0 && nd->type != 0)
			return (1);
		else if ((in_range(nd->type, 1, 2) || in_range(nd->type, 4, 5))
		&& (!nd->right || nd->right->type != 0))
			return (1);
		i++;
		nd = nd->right;
	}
	return (0);
}

int			get_tokens(t_shell **shell)
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
	(*shell)->token_count = i;
	(*shell)->tkns = tkns;
	if (error_check(tkns) == 1)
	{
		(*shell)->tree = tkns;
		return (1);
	}
	return (0);
}
