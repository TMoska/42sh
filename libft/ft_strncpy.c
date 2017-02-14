/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:45:03 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/17 19:00:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)dst;
	while (i < len && *src)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	while (i < len)
	{
		*dst = '\0';
		i++;
		dst++;
	}
	return (tmp);
}
