/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:20:31 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/22 21:07:12 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str2join(char **s1, char **s2)
{
	size_t	size1;
	size_t	size2;
	char	**new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	size1 = ft_str2len(s1);
	size2 = ft_str2len(s2);
	new = ft_str2new(size1 + size2);
	while (s1 && s1[a])
	{
		new[i] = ft_strdup(s1[a]);
		i++;
		a++;
	}
	a = 0;
	while (s2 && s2[a])
	{
		new[i] = ft_strdup(s2[a]);
		i++;
		a++;
	}
	return (new);
}
