/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 09:18:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/31 04:15:06 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	char	**table;
	int		size;
	int		i;
	int		substr_len;

	if (!s)
		return (0);
	size = ft_word_count(s, c);
	substr_len = 0;
	i = 0;
	if (!(table = (char **)malloc((sizeof(char *) * (size + 1)))))
		return (NULL);
	while (size--)
	{
		while (*s == c && *s != '\0')
			s++;
		substr_len = ft_strlen_until(s, c);
		table[i] = ft_strsub(s, 0, substr_len);
		if (!table[i])
			return (NULL);
		s += substr_len;
		i++;
	}
	table[i] = NULL;
	return (table);
}
