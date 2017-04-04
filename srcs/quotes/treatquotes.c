/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 07:01:22 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/04 06:28:34 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *temp)
{
	int		index;
	char	c;
	char	*end;

	index = 0;
	c = temp[0];
	if (ft_isquotes(c))
		end = &temp[index + 1];
	else
		end = &temp[index];
	end = ft_strdup(end);
	while (end[index])
	{
		if ((end[index] == '\\' && end[index + 1] == '\"' && c != '\'')
				|| (end[index] == '\'' && c == '\'' && end[index + 1]))
			end = ft_strndelat(end, index, 1);
		else
			++index;
	}
	if (ft_isquotes(end[index - 1]) && ft_isquotes(c))
		end[index - 1] = '\0';
	return (end);
}

char	*get_new_part(char *cmd, char **temp)
{
	int index;

	index = 0;
	while (cmd[index])
	{
		if (ft_isquotes(cmd[index]) == 0)
		{
			while (cmd[index] && (!ft_isquotes(cmd[index]) ||\
						(ft_isquotes(cmd[index]) && cmd[index - 1] == '\\')))
				++index;
			*temp = ft_strsub(cmd, 0, index);
			return (&cmd[index]);
		}
		else
		{
			*temp = ft_strsub(cmd, 0, ft_endquo(cmd, index));
			return (&cmd[ft_endquo(cmd, index)]);
		}
	}
	return (NULL);
}

char	*treat_quotes(char *cmd)
{
	char	*newcmd;
	char	*endcmd;
	char	*temp;

	endcmd = ft_strnew(1);
	while (cmd && cmd[0] != '\0')
	{
		cmd = get_new_part(cmd, &temp);
		temp = remove_quotes(temp);
		endcmd = ft_strjoin(endcmd, temp);
	}
	return (endcmd);
}
