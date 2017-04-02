/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitquote_str2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 00:00:47 by ryaoi             #+#    #+#             */
/*   Updated: 2017/04/02 11:33:27 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_count_quotes(char **ptr, int *ret, int cmd)
{
	if (cmd == 1)
	{
		(*ret)++;
		(*ptr)++;
		while (**ptr != '\0' && **ptr != '\"')
			(*ptr)++;
		if (**ptr == '\"')
			(*ptr)++;
	}
	else
	{
		(*ret)++;
		(*ptr)++;
		while (**ptr != '\0' && **ptr != '\'')
			(*ptr)++;
		if (**ptr == '\'')
			(*ptr)++;
	}
}

static int	count_quotes(char *cmd)
{
	int		ret;
	char	*ptr;

	ret = 0;
	ptr = cmd;
	while (*ptr != '\0')
	{
		if (*ptr != '\"' && *ptr != '\'' && *ptr != ' ')
		{
			ret++;
			while (*ptr != '\0' && *ptr != '\"' && *ptr != '\'' && *ptr != ' ')
				ptr++;
		}
		else if (*ptr == '\"')
			sub_count_quotes(&ptr, &ret, 1);
		else if (*ptr == '\'')
			sub_count_quotes(&ptr, &ret, 0);
		else
			ptr++;
	}
	return (ret);
}

char		*sub_splitnoquote(char *cmd, int *i)
{
	int		start;
	char	*str;

	start = *i;
	while (cmd[*i] != '\0' && cmd[*i] != '\'' && cmd[*i] != '\"'
			&& cmd[*i] != ' ')
		(*i)++;
	if (!(str = ft_strsub(cmd, start, (*i) - start)))
		return (NULL);
	return (str);
}

static char	*sub_splitquote(char *cmd, int *i, int dquote)
{
	int		start;
	char	*str;

	start = *i;
	(*i)++;
	if (dquote == 0)
	{
		while (cmd[*i] != '\0' && cmd[*i] != '\'')
			(*i)++;
		if (cmd[*i] == '\'')
			(*i)++;
	}
	else
	{
		while (cmd[*i] != '\0' && cmd[*i] != '\"')
			(*i)++;
		if (cmd[*i] == '\"')
			(*i)++;
	}
	if (!(str = ft_strsub(cmd, start, (*i) - start)))
		return (NULL);
	return (str);
}

char		**splitquote_str2(char *cmd)
{
	int		size;
	char	**array;
	int		i;
	int		j;

	i = 0;
	size = count_quotes(cmd);
	if (!(array = ft_str2new(size)))
		return (NULL);
	j = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] != '\0' && cmd[i] == ' ')
			i++;
		if (cmd[i] == '\0')
			break ;
		if (cmd[i] != '\'' && cmd[i] != '\"')
			array[j] = sub_splitnoquote(cmd, &i);
		else if (cmd[i] == '\"' || cmd[i] == '\'')
			array[j] = sub_splitquote(cmd, &i, (cmd[i] == '\"') ? 1 : 0);
		j++;
	}
	array[j] = 0;
	return (&array[0]);
}
