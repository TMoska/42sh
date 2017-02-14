/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:25:11 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/17 16:25:23 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	a;
	int	b;

	a = 0;
	if (!*little && !*big)
		return ((char *)big);
	while (big[a])
	{
		b = 0;
		while (little[b] == big[a + b] && little[b] && big[a + b])
			b++;
		if (!little[b])
			return ((char *)&big[a]);
		a++;
	}
	return (0);
}
