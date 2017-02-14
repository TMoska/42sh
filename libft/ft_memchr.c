/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:56:49 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/18 12:31:46 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n != 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		return (ft_memchr(s + 1, c, --n));
	}
	return (0);
}
