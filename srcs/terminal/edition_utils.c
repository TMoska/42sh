/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:07:59 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/28 18:19:08 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_linesize(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int		ft_currentline(t_shell **shell)
{
	char	*part;
	char	**argv;
	int		i;
	int		len;

	i = 0;
	argv = ft_strsplit((*shell)->buff, '\n');
	while (argv[i])
	{
		argv[i] = ft_strjoin(argv[i], "\n");
		++i;
	}
	part = ft_getpart(shell);
	len = (*shell)->term->tc_in;
	i = 0;
	while (argv[i] && ft_strncmp(part, argv[i], ft_strlen(part)) != 0)
	{
		len -= ft_strlen(argv[i]);
		++i;
	}
	return (len);
}

int		ft_isfirstline(t_shell **shell)
{
	int i;
	int	i2;

	i2 = 0;
	i = (*shell)->term->tc_in;
	if (i < 0)
		i = 0;
	while (i > 0)
	{
		if ((*shell)->buff[i] == '\n')
			i2++;
		if (i2 > 1)
			return (0);
		--i;
	}
	return (1);
}

char	*ft_getpart(t_shell **shell)
{
	int i;
	char	**array;
	int i2;
	int i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	array = ft_strsplit((*shell)->buff, '\n');
	while (array[i2])
	{
		array[i2] = ft_strjoin(array[i2], "\n");
		++i2;
	}
	i2 = 0;
	while (i < (*shell)->term->tc_in)
	{
		if (!array || !array[i2])
			break ;
		if (!array[i2][i3])
		{	
			i3 = 0;
			++i2;
		}
		++i;
		++i3;
	}
	return (array[i2]);
}
