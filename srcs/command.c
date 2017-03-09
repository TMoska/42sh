/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:42:06 by moska             #+#    #+#             */
/*   Updated: 2017/03/09 04:58:57 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		construct_command(t_shell **shell)
{
	t_tkn	*tkns;
	char	**cmds;
	int		i;
	int		type;

	tkns = NULL;
	i = 0;
	cmds = ft_strsplit((*shell)->buff, ' ');
	while (cmds[i])
	{
		// Todo: Double-check with mfa (2&>1) matching
		type  = (ft_strcmp(cmds[i], ";") == 0 || ft_strcmp(cmds[i], "||") == 0 \
			|| ft_strcmp(cmds[i], "&&") == 0 || ft_strcmp(cmds[i], "|") == 0 \
			|| ft_strcmp(cmds[i], "<") == 0 || ft_strcmp(cmds[i], "<<") == 0 \
			|| ft_strcmp(cmds[i], ">") == 0 || ft_strcmp(cmds[i], ">>") == 0 \
			|| ft_strstr(cmds[i], "&>"));
		tkn_new_to_back(&tkns, cmds[i], type);
		printf("! %s %i\n", cmds[i], type);
		i++;
	}
}
