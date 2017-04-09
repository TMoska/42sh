/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 05:55:01 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/08 06:56:43 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_fd_aggregator(char ***cmds, char *cmd, int *offset, int *len)
{
	char	c;
	char	*tmp_str;
	size_t	size;

	(void)cmds;
	size = 0;
	c = cmd[*offset + *len + 1];
	while (!(cmd[*offset + *len + 1 + size] == ' ' ||\
		cmd[*offset + *len + 1 + size] == '\0'))
		size++;
	if (!(tmp_str = ft_strndup(&cmd[*offset + *len + 1], size)))
		return (-1);
	if (!ft_strstr(tmp_str, ">&"))
	{
		ft_strdel(&tmp_str);
		return (-1);
	}
	add_command(cmds, cmd, offset, len);
	ft_arr_push(cmds, tmp_str);
	(*offset) += *len + 1 + size;
	ft_strdel(&tmp_str);
	return (0);
}

int				is_op(char *c)
{
	if (ft_strlen(c) >= 2 && (ft_strncmp(c, "||", 2) == 0 ||
			ft_strncmp(c, "&&", 2) == 0 || ft_strncmp(c, "<<", 2) == 0 ||
			ft_strncmp(c, ">>", 2) == 0))
		return (2);
	else if (*c == ';' || *c == '|' || *c == '<' || *c == '>')
		return (1);
	else
		return (0);
}

char			**split_command(char *cmd)
{
	char	**cmds;
	char	*c;
	int		offset;
	int		len;

	cmds = NULL;
	c = cmd;
	offset = 0;
	len = 0;
	while (*c)
	{
		c = &cmd[offset + len];
		if (*c == ' ' && is_fd_aggregator(&cmds, cmd, &offset, &len) == 0)
		{
			if (*(c = &cmd[offset]) == ' ')
				c = &cmd[offset++];
			len = 0;
		}
		else if ((is_op(c) && !ft_isescaped(cmd, offset + len)
			&& !ft_isinquotes(cmd, offset + len)) || *c == '\0')
			add_cmds(&cmds, cmd, &offset, &len);
		else
			len++;
	}
	return (cmds);
}
