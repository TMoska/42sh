/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <adeletan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:52:28 by adeletan          #+#    #+#             */
/*   Updated: 2017/04/05 05:39:43 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_endquo(const char *str, int i)
{
	char c;

	c = str[i];
	++i;
	while (str[i] && (((str[i] == c && str[i - 1] == '\\')
		|| (str[i] == '\'' && c != '\'')) || c != str[i]))
		++i;
	return (i + 1);
}

size_t		ft_strlen_quo(const char *str, char c)
{
	int			i;

	i = 0;
	while (str[i] != c && str[i])
	{
		if ((str[i] == '"' || str[i] == '`' || str[i] == 39) &&
				(str[i - 1] != '\\'))
			i = ft_endquo(str, i) + 1;
		else
			++i;
	}
	return (i);
}

static int	ft_count_quo(char const *s, char c)
{
	size_t	i;
	int		wc;
	int		found;

	i = 0;
	wc = 0;
	found = 0;
	while (s[i] && i < ft_strlen(s))
	{
		if (s[i] == c)
			found = 0;
		else
		{
			if ((s[i] == '`' || s[i] == '"' || s[i] == 39) && s[i - 1] != '\\')
				i = ft_endquo(s, i);
			if (found == 0)
				wc++;
			found = 1;
		}
		i++;
	}
	return (wc);
}

char		**ft_splitquotes(char const *s, char c)
{
	char	**table;
	int		size;
	int		i;
	int		substr_len;

	if (!s)
		return (0);
	size = ft_count_quo(s, c);
	substr_len = 0;
	i = 0;
	if (!(table = ft_str2new(size)))
		return (NULL);
	while (size--)
	{
		while (*s == c && *s != '\0')
			s++;
		substr_len = ft_strlen_quo(s, c);
		table[i] = ft_strncpy(ft_strnew(substr_len), s, substr_len);
		if (!table[i])
			return (NULL);
		s += substr_len;
		i++;
	}
	table[i] = NULL;
	return (table);
}
