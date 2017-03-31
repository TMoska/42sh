/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 09:18:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/31 04:15:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_u(const char *str, char c)
{
	const char *s;

	s = str;
	while (*s != c && *s != '\0')
		++s;
	if (*s == c)
		++s;
	return (s - str);
}

static int		ft_word_countu(char const *s, char c)
{
	int found;
	int	index;

	index = 1;
	found = 0;
	while (s[index])
	{
		if (s[index] == c)
			found++;
		++index;
	}
	if (s[index - 1] != c)
		++found;
	return (found);
}

char			**ft_strsplitin(char const *s, char c)
{
	char	**table;
	int		size;
	int		i;
	int		substr_len;

	if (!s)
		return (0);
	size = ft_word_countu(s, c);
	substr_len = 0;
	i = 0;
	if (!(table = (char **)malloc((sizeof(char *) * (size + 1)))))
		return (NULL);
	while (size--)
	{
		substr_len = ft_strlen_u(s, c);
		table[i] = ft_strsub(s, 0, substr_len);
		if (!table[i])
			return (NULL);
		s += substr_len;
		i++;
	}
	table[i] = NULL;
	return (table);
}
