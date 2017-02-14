/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:18:37 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 07:31:32 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*string;
	char	*tmp;

	if (!s)
		return (0);
	tmp = NULL;
	if ((string = (char *)malloc(len + 1)))
	{
		tmp = string;
		while (len > 0)
		{
			*tmp = s[start];
			tmp++;
			start++;
			len--;
		}
		*tmp = '\0';
	}
	else
		return (0);
	return (string);
}
