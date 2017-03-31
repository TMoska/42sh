/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:38:50 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/30 20:18:14 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*ft_setquotes(int *array, const char *s, char c)
{
	int		found;
	int		wc;
	int		i;

	i = -1;
	wc = 0;
	found = 0;
	while (s[++i])
		if (s[i] == c)
			found = 0;
		else
		{
			if ((s[i] == '`' || s[i] == '"' || s[i] == 39) && s[i - 1] != '\\')
			{
				if (s[i] == '\'')
					array[wc] = 1;
				i = ft_endquo(s, i);
			}
			if (found == 0)
				wc++;
			found = 1;
		}
	return (array);
}

void	ft_echo(t_shell **shell, char *str, int flag)
{
	int		i;
	int		i2;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !flag)
		{
			if ((ft_strncmp(&str[i], "$?", 2) == 0) && (i += 2))
				ft_putnbr((*shell)->ret);
			else
			{
				i2 = i;
				while (str[i] && (!ft_isspace(str[i]) &&
					!ft_isquotes(str[i + 1])))
					++i;
				tmp = ft_strsub(str, i2 + 1, i - 1);
				ft_putstr(get_env_val(shell, tmp));
				ft_strdel(&tmp);
			}
		}
		(str[i]) ? ft_putchar(str[i++]) : (0);
	}
}

int		builtin_echo(t_shell **shell, char *cmd)
{
	int		i;
	char	**array;
	int		*iarray;

	array = ft_splitquotes(cmd, ' ');
	i = 1;
	iarray = ft_memalloc(sizeof(int) * (ft_str2len(array) + 1));
	iarray = ft_setquotes(iarray, (cmd + 4), ' ');
	if (ft_strcmp(array[1], "-n") == 0)
		++i;
	while (array[i])
	{
		ft_echo(shell, array[i], iarray[i - 1]);
		++i;
		if (array[i])
			ft_putchar(' ');
	}
	if (ft_strcmp(array[1], "-n") != 0)
		ft_putchar('\n');
	ft_str2del(&array);
	free(iarray);
	return (0);
}
