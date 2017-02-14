/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 09:18:00 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 14:52:07 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_count(char const *s, char c)
{
	int	i;
	int	wc;
	int	found;

	i = 0;
	wc = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == c)
			found = 0;
		else
		{
			if (found == 0)
				wc++;
			found = 1;
		}
		i++;
	}
	return (wc);
}

static void	skip_separator(char *s, int *i, char c)
{
	while (s[*i] == c)
		*i = *i + 1;
}

static char	**allocate_word_memory(char **table, char *s, char c)
{
	int	i;
	int	b;
	int	d;

	i = 0;
	b = 0;
	d = 0;
	skip_separator(s, &i, c);
	while (s[i] != '\0')
	{
		i++;
		if (s[i] == c || s[i] == '\0')
		{
			if ((table[b] = (char *)malloc(sizeof(char) * (d + 1))))
			{
				b++;
				d = 0;
				skip_separator(s, &i, c);
			}
			else
				return (0);
		}
		d++;
	}
	return (table);
}

static char	**allocate_words(char **table, char *s, char d)
{
	int	i;
	int	b;
	int	c;

	i = 0;
	b = 0;
	c = 0;
	skip_separator(s, &i, d);
	while (s[i] != '\0')
	{
		table[b][c] = s[i];
		i++;
		c++;
		if (s[i] == d)
		{
			table[b][c] = '\0';
			b++;
			c = 0;
			skip_separator(s, &i, d);
		}
	}
	return (table);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**table;
	int		size;

	if (!s)
		return (0);
	size = word_count(s, c);
	if ((table = (char **)malloc(sizeof(*table) * (size + 1))))
	{
		table[size] = 0;
		table = allocate_word_memory(table, (char *)s, c);
		table = allocate_words(table, (char *)s, c);
		return (table);
	}
	else
		return (0);
	return (0);
}
