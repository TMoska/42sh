/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 05:55:01 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/17 17:28:34 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_command(char ***cmds, char *cmd, int *offset, int *len)
{
	char	*tmp;
	char	*tmp1;

	if (*len == 0)
		return ;
	tmp = ft_strndup(&cmd[*offset], *len);
	tmp1 = ft_strtrim(tmp);
	ft_arr_push(cmds, tmp1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
}

static int		is_fd_aggregator(char ***cmds, char *cmd, int *offset, int *len)
{
	char	c;
	char	*tmp_str;
	size_t	size;

	(void)cmds;
	size = 0;
	c = cmd[*offset + *len + 1];
	while (!(cmd[*offset + *len + 1 + size] == ' ' || cmd[*offset + *len + 1 + size] == '\0'))
		size++;
	tmp_str = ft_strndup(&cmd[*offset + *len + 1], size);
	if (!ft_strstr(tmp_str, ">&"))
	{
		ft_strdel(&tmp_str);
		return (-1);
	}
	add_command(cmds, cmd, offset, len);
	ft_arr_push(cmds, tmp_str);
	(*offset) += (size + 1);
	return (0);
}

static int		is_op(char *c)
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

static void		add_operator(char ***cmds, char *cmd, int *offset, int *len)
{
	int		len_op;
	char	*tmp;
	char	*tmp1;

	len_op = is_op(&cmd[*offset + *len]);
	if (!len_op || !(tmp = ft_strndup(&cmd[*offset + *len], len_op)))
		return ;
	ft_arr_push(cmds, tmp);
	tmp1 = ft_strtrim(tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	(*offset) += len_op;
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
		// Todo: 2>&1
		if (*c == ' ' && is_fd_aggregator(&cmds, cmd, &offset, &len) == 0)
		{
			c = &cmd[offset + len];
			len = 0;
			continue ;
		}
		if (is_op(c) || *c == '\0')
		{
			add_command(&cmds, cmd, &offset, &len);
			add_operator(&cmds, cmd, &offset, &len);
			offset += len;
			len = 0;
		}
		else
			len++;
	}
	return (cmds);
}
