/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 05:55:01 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/09 08:54:06 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define OP(c) (c == ';' || c == '|' || c == '<' || c == '>')

/*
**	Basically, this is a modified version of ft_strsplit to match 21sh operators
*/

void	add_command(char ***cmds, char *cmd, int *offset, int *len)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strndup(&cmd[*offset], *len);
	tmp1 = ft_strtrim(tmp);
	ft_arr_push(cmds, tmp1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
}

void	add_operator(char ***cmds, char *cmd, int *offset, int *len)
{
	int		len_op;
	char	*tmp;
	char	*tmp1;

	len_op = 0;
	while (OP(cmd[*offset + *len + len_op]))
		len_op++;
	if (!len_op || !(tmp = ft_strndup(&cmd[*offset + *len], len_op)))
		return ;
	ft_arr_push(cmds, tmp);
	tmp1 = ft_strtrim(tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	(*offset) += len_op;
}

char	**split_command(char *cmd)
{
	char	**cmds;
	char	c;
	int		offset;
	int		len;

	cmds = NULL;
	c = *cmd;
	offset = 0;
	len = 0;
	while (c)
	{
		c = cmd[offset + len];
		// Todo: 2&>1, >>, <<, ||, &&
		if (OP(c) || c == '\0')
		{
			add_command(&cmds, cmd, &offset, &len);
			add_operator(&cmds, cmd, &offset, &len);
			offset += len;
			len = 0;
		}
		len++;
	}
	return (cmds);
}
