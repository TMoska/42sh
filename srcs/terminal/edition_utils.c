/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 05:07:59 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/11 14:59:48 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_numberline(t_shell **shell)
{
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	ft_getpart(shell, &tmp);
	len = ft_strlen(tmp);
	while (len >= (size_t)ft_linesize())
	{
		len -= ft_linesize();
		++i;
	}
	ft_strdel(&tmp);
	return (i);
}

int			ft_linesize(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int			ft_currentline(t_shell **shell)
{
	char	**argv;
	int		i;
	int		i2;
	int		i3;
	char	*tmp;

	i = -1;
	argv = ft_strsplitin((*shell)->buff, '\n');
	ft_getpart(shell, &tmp);
	while (argv[++i] && ft_strncmp(argv[i], tmp, ft_strlen(argv[i])) != 0)
		;
	i3 = (*shell)->term->tc_in;
	i2 = 0;
	while (i2 < i)
		i3 -= ft_strlen(argv[i2++]);
	ft_strdel(&tmp);
	ft_str2del(&argv);
	return (i3);
}

int			ft_isfirstline(t_shell **shell)
{
	int i;
	int	i2;

	i2 = 0;
	i = (*shell)->term->tc_in;
	if (i < 0)
		i = 0;
	while (i > 0)
	{
		if ((*shell)->buff[i] == '\n' && i != (*shell)->term->tc_in)
			i2++;
		if (i2 != 0)
			return (0);
		--i;
	}
	return (1);
}

int			ft_getpart(t_shell **shell, char **str)
{
	int		i;
	char	**array;
	int		i2;
	int		i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	if (!(array = ft_strsplitin((*shell)->buff, '\n')))
	{
		str ? ft_strdup("\0") : NULL;
		return (0);
	}
	i2 = 0;
	while (i2 < (*shell)->term->tc_in && (*shell)->term->tc_in != 0)
	{
		i2 += ft_strlen(array[i]);
		i++;
	}
	if (i != 0)
		i--;
	i3 = ft_strlen(array[i]);
	str ? *str = ft_strdup(array[i]) : NULL;
	ft_str2del(&array);
	return (i3);
}
