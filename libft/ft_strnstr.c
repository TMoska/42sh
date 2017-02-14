/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:24:07 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/17 16:24:56 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!*little && !*big)
	{
		return ((char *)big);
	}
	while (big[a] && (a < len))
	{
		b = 0;
		while (little[b] == big[a + b] && little[b] &&
				big[a + b] && ((a + b) < len))
			b++;
		if (!little[b])
			return ((char *)&big[a]);
		a++;
	}
	return (0);
}
