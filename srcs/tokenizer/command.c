/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 10:46:19 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		assign_a_priority_type(char *s, int *type)
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

void		construct_command(t_shell **shell)
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
		printf("! |%s| %i\n", cmds[i], type);
		i++;
	}
	ft_str2del(&cmds);
	(*shell)->tkns = tkns;
}
