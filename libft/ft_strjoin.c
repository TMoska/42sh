/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:34:04 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 07:51:57 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	char	*tmp;

	tmp = NULL;
	if (s1 && s2)
	{
		if ((string = (char *)malloc(ft_strlen((char *)s1) +
			ft_strlen((char *)s2) + 1)))
		{
			tmp = string;
			while (*s1)
				*tmp++ = *s1++;
			while (*s2)
				*tmp++ = *s2++;
			*tmp = '\0';
		}
		else
			return (0);
		return (string);
	}
	return (0);
}
