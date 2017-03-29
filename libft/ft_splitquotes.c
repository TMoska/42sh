/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeletan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:52:28 by adeletan          #+#    #+#             */
/*   Updated: 2017/03/29 03:40:01 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static char			*ft_strncpyquo(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	d;
	char	*tmp;

	i = 0;
	tmp = (char *)dst;
	d = *src;
	while (i++ < len && *src)
	{
		if ((*(src + 1) == d || !ft_isquotes(d)) && *src == '\\' && (*(src + 1)
		== '"' || *(src + 1) == '`' || *(src + 1) == 39) && (d = *(src + 1)))
			++src;
		if ((*src == '"' || *src == '`' || *src == 39) && *(src - 1) != '\\' &&
			(*src == d || !ft_isquotes(d)) && (d = *src))
			++src;
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
	while (i++ < len)
		*(dst++) = '\0';
	return (tmp);
}

int					ft_endquo(const char *str, int i)
{
	int		quotes_count;
	char	c;
	int		current_end;
	int		temp_end;

	c = str[i];
	quotes_count = 1;
	current_end = i;
	temp_end = current_end;
	while (str[++i])
	{
		if (str[i] == c && !ft_isspace(str[i + 1]) && str[i - 1] != '\\')
		{
			++quotes_count;
			temp_end = i;
		}
		if (str[i] == c && ft_isspace(str[i + 1]) && str[i - 1] != '\\')
		{
			--quotes_count;
			current_end = i;
		}
		if (quotes_count == 0)
			return (current_end);
	}
	return (temp_end);
}

static size_t		ft_strlen_quo(const char *str, char c)
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

static int			ft_count_quo(char const *s, char c)
{
	int		i;
	int		wc;
	int		found;

	i = 0;
	wc = 0;
	found = 0;
	while (s[i])
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

char				**ft_splitquotes(char const *s, char c)
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
		table[i] = ft_strncpyquo(ft_strnew(substr_len), s, substr_len);
		if (!table[i])
			return (NULL);
		s += substr_len;
		i++;
	}
	table[i] = NULL;
	return (table);
}
