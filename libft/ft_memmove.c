/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:48:16 by tmoska            #+#    #+#             */
/*   Updated: 2016/11/20 15:02:34 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *tmp;

	tmp = dst;
	if (src <= dst)
		while (len--)
			tmp[len] = ((unsigned char *)src)[len];
	else
		ft_memcpy(dst, src, len);
	return ((void *)dst);
}
